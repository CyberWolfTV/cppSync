#include "../Location.hpp"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


// the backup function calls this method directly
void my::Location::compare(std::string source, std::string target, bool output){
    // source -> from main instance (newer one)
    // target -> from backup locations (older one)
    std::map<std::string, std::string> source_states = get_state(source);
    std::map<std::string, std::string> target_states = get_state(target);

    // Lets create a map with all paths, so we can take a look on how
    // they changed.
    std::map<std::string, bool> all_paths;
    for(auto i = target_states.begin(); i != target_states.end(); i++){
        all_paths[i->first] = true;
    }
    for(auto i = source_states.begin(); i != source_states.end(); i++){
        all_paths[i->first] = true;
    }

    /*
     * In the following for-loop the paths will be sorted in different vectors/maps.
     * Algorithmen explained:
     * changed [vector]:
     *  1. Both maps have a hash for a given part.
     *  2. These hashes differ.
     *
     * moved_created [map]:
     *  1. The newer state (source) has a hash for the given path.
     *  2. The older state (target) does not have a hash for the given path.
     *
     * moved_deleted [map]:
     *  1. The older state (target) has a hash for the given path.
     *  2. The newer state (source) does not have a hash for the given path.
     */
    std::string target_hash;
    std::string source_hash;
    std::map<std::string, std::string> moved_deleted;
    std::map<std::string, std::string> moved_created;

    for(auto i = all_paths.begin(); i != all_paths.end(); i++){
        target_hash = target_states[i->first];
        source_hash = source_states[i->first];
        
        if(target_hash == source_hash){
            target_states.erase(i->first);
            source_states.erase(i->first);
        }
        else if(target_hash == ""){
            moved_created[i->first] = source_hash;
        }
        else if(source_hash == ""){
            moved_deleted[i->first] = target_hash;
        }
        else if(target_hash != source_hash){
            changed.push_back(i->first);
            target_states.erase(i->first);
            source_states.erase(i->first);
        }
        else{
            std::cerr << "ERROR: COMPARE FUNCTION" << std::endl;
        }
    }


    bool found = false;
    typedef std::multimap<std::string, std::string>::iterator multimap_iterator;
    
    for(auto i = moved_created.begin(); i != moved_created.end(); i++){
        for(auto j = target_states.begin(); j != target_states.end(); i++){
            if(i->second == j->second){
                moved[j->first] = i->first;
                found = true;
            }
        }
        if(!found){
            created.push_back(i->first);
        }
        found = false;
    }

    for(auto i = moved_deleted.begin(); i != moved_deleted.end(); i++){
        for(auto j = source_states.begin(); j != source_states.end(); i++){
            if(i->second == j->second){
                moved[i->first] = j->first;
                found = true;
            }
        }
        if(!found){
            deleted.push_back(i->first);
        }
        found = false;
    }  

    if(output){
        print_compared();
    }
    return;
}


// includes output to file
void my::Location::print_compared(){
    // Print results
    std::fstream output_file;
    std::string filename = ".cppSync/what_changed/" + datetime;
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
    return;
}


void my::Location::compare(){
    // choose states
    std::cout << "Which state do u want to compare?" << std::endl;
    std::cout << "First state (usually the older one): " << std::endl;
    std::string target = ".cppSync/hashes/" + get_choice();
    
    std::cout << "\nSecond state (usually the newer one): " << std::endl;
    std::string source = ".cppSync/hashes/" + get_choice();

    compare(source, target, true);
    return;
}
