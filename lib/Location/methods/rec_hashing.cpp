#include "../Location.hpp"
#include "../../lib/myLib/MyJSON.hpp"
#include "../../lib/myLib/sha256.hpp"

#include <map>
#include <experimental/filesystem>
#include <fstream>


namespace fs = std::experimental::filesystem;


bool my::Location::is_in_scope(std::string dir_entry){
    // always exclude .cppSync
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
    // actual hashing
    rec_hashing(".");

    // write json stuff to file (ordered ...)
    my::MyJSON json_hashes;
    for(auto i = map_with_hashes.begin(); i != map_with_hashes.end(); i++){
        json_hashes.addpair(i->first, i->second);
    }

    std::string path = ".cppSync/hashes/" + datetime;
    std::ofstream FileWithHashes(path);
    FileWithHashes << json_hashes.get() << std::endl;
    FileWithHashes.close();
}