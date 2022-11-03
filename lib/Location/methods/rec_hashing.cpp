#include "../Location.hpp"
#include "../../lib/myLib/MyJSON.hpp"
#include "../../lib/myLib/sha256.hpp"

#include <map>
#include <experimental/filesystem>
#include <fstream>


namespace fs = std::experimental::filesystem;


bool my::Location::is_in_scope(std::string dir_entry){
    // always exclude .git & .cppSync
    return true;
}

void my::Location::rec_hashing(std::string name){
    const fs::path this_loc{name};
    for (auto const& dir_entry : fs::directory_iterator{this_loc}){
        if(is_in_scope(dir_entry.path().string())){
            if(fs::is_regular_file(dir_entry.path())){
                // insert path (key) and hash(value) into the map
                map_with_hashes.insert(std::pair<std::string, std::string>(dir_entry.path().string(), sha256(dir_entry.path().string())));
            }
            else if(fs::is_directory(dir_entry.path())){
                rec_hashing(dir_entry.path().string());
            }
        }
    }
}

void my::Location::get_hashes(){
    my::MyJSON json_hashes;

    rec_hashing(".");

    // write json stuff to file

    // TODO iterate through created map, dont just dump em above!
}