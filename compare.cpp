#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <experimental/filesystem>

#include "lib/myLib/MyJSON.hpp"

namespace fs = std::experimental::filesystem;


namespace my{
    
    int choice(int i){
        int choice;
        std::cin >> choice;
        if(choice > i+1){
            return my::choice(i);
        } else{
            return choice;
        }
    }

    std::string get_choice(int which_time, std::map<std::string, int> *options){

        const fs::recursive_directory_iterator end{};
        std::map<int, std::string> files;

        // List options (all files in the hashes directory)
        int counter = 0;
        for(fs::recursive_directory_iterator i{"."}; i != end; ++i){
            std::string filename = i->path().string();
            filename.erase(0,2);
            if(options->operator[]("compare-default") == 0){
                std::cout << "[" << counter << "] " << filename << std::endl;
            }
            files[counter] = filename;
            counter++;
        }

        // Which one do u wanna?
        int choice;
        if(options->operator[]("compare-default") == 0){
            if(which_time == 1){
                std::cout << "Choose a state to compare with (usually the older one)." << std::endl;
            } else if(which_time == 2){
                std::cout << "Choose a second state to compare with (usually the newer one)." << std::endl;
            }
            choice = my::choice(counter);
        } else if(which_time == 1){
            choice = 1;
        } else if(which_time == 2){
            choice = 0;
        }
        return files[choice];
    }

    void get_states(std::map<std::string, std::string> *Choice1, std::map<std::string, std::string> *Choice2, std::string *oldpath, std::string *name, std::map<std::string, int> *options){

        std::string newpath = *oldpath + "/" + *name + "/.cppSync/hashes";
        fs::current_path(newpath);
        

        // Choice 1
        std::string choice = get_choice(1, options);

        auto stringstream = std::ostringstream{};
        std::ifstream input_file(choice);
        if (!input_file.is_open()) {
            std::cerr << "could not open file " << choice << std::endl;;
            exit(EXIT_FAILURE);
        }
        stringstream << input_file.rdbuf();

        std::string json_of_choice = stringstream.str();
        importJsonObject_to_map(json_of_choice, Choice1);
        input_file.close();

        
        // Choice 2
        choice = get_choice(2, options);

        auto stringstream2 = std::ostringstream{};
        std::ifstream input_file2(choice);
        if (!input_file2.is_open()) {
            std::cerr << "could not open file " << choice << std::endl;;
            exit(EXIT_FAILURE);
        }
        stringstream2 << input_file2.rdbuf();

        json_of_choice = stringstream2.str();
        importJsonObject_to_map(json_of_choice, Choice2);
        input_file2.close();


        fs::current_path(*oldpath);
    }

    void compare(std::map<std::string, int> *options, std::string *name, std::string *datetime, std::vector<std::string> *created, std::vector<std::string> *changed, std::vector<std::string> *deleted,std::map<std::string, std::string> *moved){

        if(options->operator[]("compare-default") == 0){
            std::cout << "U have to choose 2 States which should be compared." << std::endl;
            std::cout << "0 for the current & 1 for the last state." << std::endl;
        }

        std::map<std::string, std::string> Choice1; // older hashes
        std::map<std::string, std::string> Choice2; // newer hashes
        std::string oldpath = fs::current_path();
        
        // get the states, via the maps
        get_states(&Choice1, &Choice2, &oldpath, name, options);

// Choice1 & 2 are loaded (100% sure), files read etc.
//#####################################################################################################################

        // Lets create a map with all paths, so we can take a look on how they changed
        std::map<std::string, int> all_paths;
        for(auto i = Choice2.begin(); i != Choice2.end(); i++){
            all_paths[i->first] = 1;
            //std::cerr << "\n\n\n" << i->first << "\n\n\n";
        }
        for(auto i = Choice1.begin(); i != Choice1.end(); i++){
            all_paths[i->first] = 1;
            //std::cout << i->first << std::endl;
            //std::cout << i->second << std::endl;
        }

        std::map<std::string, std::string> moved_deleted;
        std::map<std::string, std::string> moved_created;

        std::cout << "all_paths.size() = " << all_paths.size() << std::endl;

        /*
         *  In the following for-loop the paths will be sorted in different vectors/maps.
         *  If a file got created the path wont be included in map "Choice1", if it got deleted it wont be in "Choice2".
         *  If a file got moved the new path wont be in "Choice1" and the old one wont be in "Choice2".
         *  
         *  Creating entry1 and entry2 wont cause any problems even if the path does not exist in the map,
         *  but when accessing it through "entry1(/2)->second" it will lead to a crash.
         *  -> so i created the to strings in try-catch statements to avoid seg.-faults.
         */
        std::string hash1;
        std::string hash2;
        for(auto i = all_paths.begin(); i != all_paths.end(); i++){
            hash1 = "";
            hash2 = "";

            auto entry1 = Choice1.find(i->first);
            auto entry2 = Choice2.find(i->first);
            
            std::cout << i->first << std::endl;
            //std::cout << entry1->second << std::endl;
            //std::cout << entry2->second << std::endl << std::endl;

            try{
                hash1 = entry1->second;
            } catch (std::bad_alloc &ba){/*This path dont exist in Choice1*/}
            try{
                hash2 = entry2->second;
            } catch (std::bad_alloc &ba){/*This path dont exist in Choice2*/}
            
            if(hash1 == hash2){
                Choice1.erase(i->first);
                Choice2.erase(i->first);
            }
            else if(hash1 == ""){
                moved_created[i->first] = entry2->second;
            }
            else if(hash2 == ""){
                moved_deleted[i->first] = Choice1[i->first];
            }
            else if(hash1 != hash2){
                changed->push_back(i->first);
                Choice1.erase(i->first);
                Choice2.erase(i->first);
            }
            else{
                std::cerr << "ERROR: COMPARE FUNCTION" << std::endl;
            }
        }
// TILL HERE EVERYTHING IS FINE!
//############################################################################################################
        
        // bool found for determinging wether to push it into the created vector
        bool found = false;
        
        //std::cout << "moved_created.size() = " << moved_created.size() << std::endl;
        // moved_created
        for(auto i = moved_created.begin(); i != moved_created.end(); i++){
            // if checksum is in Choice1 file got move, else created
            std::string checksum = i->second;
            std::cout << checksum << std::endl;
            for(auto i1 = Choice1.begin(); i1 != Choice1.end(); i1++){
                if(i1->second == checksum){
                    found = true;
                    // file got moved
                    moved->operator[](i->first) = i1->first;
                }
            }
            if(!found){
                std::cout << "HI if" << std::endl;
                created->push_back(i->first);
            } else{
                std::cout << "HI else" << std::endl;
                found = false;
            }
        }

        for(auto i = moved_deleted.begin(); i != moved_deleted.end(); i++){
            // if checksum is in Choice2 file got move, else created
            std::string checksum = i->second;
            for(auto i1 = Choice2.begin(); i1 != Choice2.end(); i1++){
                if(i1->second == checksum){
                    found = true;
                    // file got moved
                    moved->operator[](i1->first) = i->first;
                }
            }
            if(!found){
                deleted->push_back(i->first);
            } else{
                found = false;
            }
        }


        // Print results
        std::fstream output_file;
        std::string filename = *name + "/.cppSync/what_changed/" + *datetime;
        output_file.open(filename,std::ios::out);

        std::cout << "These Files have been created:" << std::endl;
        output_file << "These Files have been created:" << std::endl;
        if(created->empty()){
            std::cout << "No Files have been created." << std::endl;
            output_file << "No Files have been created." << std::endl;
        } else{
            for(auto i = created->begin(); i != created->end(); i++){
                std::cout << *i << std::endl;
                output_file << *i << std::endl;
            }
        }
        output_file << "\n";
        std::cout << std::endl;

        std::cout << "These Files have been changed:" << std::endl;
        output_file << "These Files have been changed:" << std::endl;
        if(created->empty()){
            std::cout << "No Files have been changed." << std::endl;
            output_file << "No Files have been changed." << std::endl;
        } else{
            for(auto i = changed->begin(); i != changed->end(); i++){
                std::cout << *i << std::endl;
                output_file << *i << std::endl;
            }
        }
        output_file << "\n";
        std::cout << std::endl;

        std::cout << "These Files have been deleted:" << std::endl;
        output_file << "These Files have been deleted:" << std::endl;
        for(auto i = deleted->begin(); i != deleted->end(); i++){
            std::cout << *i << std::endl;
            output_file << *i << std::endl;
        }
        output_file << "\n";
        std::cout << std::endl;

        std::cout << "These Files have been moved:" << std::endl;
        output_file << "These Files have been moved:" << std::endl;
        for(auto i = moved->begin(); i != moved->end(); i++){
            std::cout << "from " << i->second <<  "\n    -> " << i->first << std::endl;
            output_file << "from " << i->second <<  "\n    -> " << i->first << std::endl;
        }
    }
}