#include "../Location.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

#include "../../helper_functions/helper_functions.hpp"

namespace fs = std::filesystem;

#define PAIR std::pair<const std::string, std::string>


void Location::backup(){
    json backed_up_hashes;
    for(auto & loc : configs.backup_locations){
        // compare the main and the loc states here
        // maybe no or just some will already have states saved
        // make sure it wont get hashed twice
        // it may helps to put every kind of change in a separate loop
        for(PAIR i: file_hashes){
            if(loc.is_in_scope(i.first)){   // is_in_scope for main loc is already in hashing...
                fs::path source = fs::path(path) / fs::path(i.first);
                fs::path target_parent = fs::path(loc.path) / fs::path(i.first).parent_path();
                fs::create_directories(target_parent);
                fs::copy(source, target_parent, fs::copy_options::overwrite_existing);

                backed_up_hashes.addpair(i.first, i.second);
            }
        }
        fs::path file_path = fs::path(loc.path) / fs::path(".cppSync/hashes/" + DATE_TIME);
        std::ofstream file_with_hashes(file_path);
        file_with_hashes << backed_up_hashes.get() << std::endl;
        file_with_hashes.close();
    }
}
