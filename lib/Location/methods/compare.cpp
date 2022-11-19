#include "../Location.hpp"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


// the backup function calls this method directly
void my::Location::compare(std::string source, std::string target){
    // source -> from main instance (newer one)
    // target -> from backup locations (older one)
    std::map<std::string, std::string> source_states = get_state(".cppSync/hashes", source);
    std::map<std::string, std::string> target_states = get_state(".cppSync/hashes", target);

    std::map<std::string, std::string> moved_deleted;
    std::map<std::string, std::string> moved_created;

    // Lets create a map with all paths, so we can take a look on how they changed
    std::map<std::string, int> all_paths;
    for(auto i = target_states.begin(); i != target_states.end(); i++){
        all_paths[i->first] = 1;
        //std::cerr << "\n\n\n" << i->first << "\n\n\n";
    }
    for(auto i = source_states.begin(); i != source_states.end(); i++){
        all_paths[i->first] = 1;
        //std::cout << i->first << std::endl;
        //std::cout << i->second << std::endl;
    }

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

        auto entry1 = target_states.find(i->first);
        auto entry2 = source_states.find(i->first);
        
        std::cout << i->first << std::endl;
        try{
            hash1 = entry1->second;
        } catch (std::bad_alloc &ba){/*This path dont exist in Choice1*/}
        try{
            hash2 = entry2->second;
        } catch (std::bad_alloc &ba){/*This path dont exist in Choice2*/}
            
        if(hash1 == hash2){
            target_states.erase(i->first);
            source_states.erase(i->first);
        }
        else if(hash1 == ""){
            moved_created[i->first] = entry2->second;
        }
        else if(hash2 == ""){
            moved_deleted[i->first] = source_states[i->first];
        }
        else if(hash1 != hash2){
            changed.push_back(i->first);
            target_states.erase(i->first);
            source_states.erase(i->first);
        }
        else{
            std::cerr << "ERROR: COMPARE FUNCTION" << std::endl;
        }
    }

    // bool found for determinging wether to push it into the created vector
    bool found = false;
        
    //std::cout << "moved_created.size() = " << moved_created.size() << std::endl;
    // moved_created
    for(auto i = moved_created.begin(); i != moved_created.end(); i++){
        // if checksum is in Choice1 file got move, else created
        std::string checksum = i->second;
        std::cout << checksum << std::endl;
        for(auto i1 = target_states.begin(); i1 != target_states.end(); i1++){
            if(i1->second == checksum){
                found = true;
                // file got moved
                moved[i->first] = i1->first;
            }
        }
        if(!found){
            created.push_back(i->first);
        } else{
            found = false;
        }
    }

    for(auto i = moved_deleted.begin(); i != moved_deleted.end(); i++){
        // if checksum is in Choice2 file got move, else created
        std::string checksum = i->second;
        for(auto i1 = source_states.begin(); i1 != source_states.end(); i1++){
            if(i1->second == checksum){
                found = true;
                // file got moved
                moved[i1->first] = i->first;
            }
        }
        if(!found){
            deleted.push_back(i->first);
        } else{
            found = false;
        }
    }
    print_compared();
}


// includes output to file
void my::Location::print_compared(){
     // Print results
    std::fstream output_file;
    std::string filename = ".cppSync/what_changed/" + DATETIME;
    output_file.open(filename,std::ios::out);

    std::cout << "These Files have been created:" << std::endl;
    output_file << "These Files have been created:" << std::endl;
    if(created.empty()){
        std::cout << "No Files have been created." << std::endl;
        output_file << "No Files have been created." << std::endl;
    } else{
        for(auto i = created.begin(); i != created.end(); i++){
            std::cout << *i << std::endl;
            output_file << *i << std::endl;
        }
    }
    output_file << "\n";
    std::cout << std::endl;

    std::cout << "These Files have been changed:" << std::endl;
    output_file << "These Files have been changed:" << std::endl;
    if(created.empty()){
        std::cout << "No Files have been changed." << std::endl;
        output_file << "No Files have been changed." << std::endl;
    } else{
        for(auto i = changed.begin(); i != changed.end(); i++){
            std::cout << *i << std::endl;
            output_file << *i << std::endl;
        }
    }
    output_file << "\n";
    std::cout << std::endl;

    std::cout << "These Files have been deleted:" << std::endl;
    output_file << "These Files have been deleted:" << std::endl;
    for(auto i = deleted.begin(); i != deleted.end(); i++){
        std::cout << *i << std::endl;
        output_file << *i << std::endl;
    }
    output_file << "\n";
    std::cout << std::endl;

    std::cout << "These Files have been moved:" << std::endl;
    output_file << "These Files have been moved:" << std::endl;
    for(auto i = moved.begin(); i != moved.end(); i++){
        std::cout << "from " << i->second <<  "\n    -> " << i->first << std::endl;
        output_file << "from " << i->second <<  "\n    -> " << i->first << std::endl;
    }
}


void my::Location::compare(){
    // choose states
    std::cout << "Which state do u want to compare?" << std::endl;
    std::cout << "First state (usually the older one): " << std::endl;
    std::string target = get_choice();
    
    std::cout << "\nSecond state (usually the newer one): " << std::endl;
    std::string source = get_choice();

    compare(source, target);
}
