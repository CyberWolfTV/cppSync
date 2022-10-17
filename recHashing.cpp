#include <string>
#include <map>
#include <experimental/filesystem>
#include <fstream>

#include "lib/myLib/MyJSON.h"
#include "lib/sha256/sha256.h"

namespace fs = std::experimental::filesystem;

namespace my{
    
    // check wether the dir is in scope (white- or blacklist defined in .config)
    bool is_in_scope(std::string dir_entry_path){
        return true;
    }




    void recHashing(std::string name, std::map<std::string, std::string> *map_of_hashes, my::MyJSON *json_hashes){

        const fs::path name_as_path{name};
        for (auto const& dir_entry : fs::directory_iterator{name_as_path}){
            if(is_in_scope(dir_entry.path().string())){
                if(fs::is_regular_file(dir_entry.path())){
                    auto stringstream = std::ostringstream{};
                    std::ifstream input_file(dir_entry.path());
                    if (!input_file.is_open()) {
                        std::cout << "could not open file: " << dir_entry.path() << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    stringstream << input_file.rdbuf();
                    std::string hash = sha256(stringstream.str());
                    map_of_hashes->insert(std::pair<std::string, std::string>(dir_entry.path(), hash));
                    json_hashes->addpair(dir_entry.path().string(), hash);
                }
                else if(fs::is_directory(dir_entry.path())){
                    recHashing(dir_entry.path().string(), map_of_hashes, json_hashes);
                }
            }
        }
    }

    

    void get_hashes(std::string *name, std::string *datetime, std::map<std::string, std::string> *map_of_hashes){
        my::MyJSON json_hashes;
        // if its crashing down here look at the map pointer
        recHashing(*name, map_of_hashes, &json_hashes);


        // write json to file
        std::string oldpath = fs::current_path();
        std::string newpath = oldpath + "/" + *name + "/.cppSync/hashes";
        fs::current_path(newpath);
        std::ofstream FileWithHashes(*datetime);
        FileWithHashes << json_hashes.get() << std::endl;
        fs::current_path(oldpath);
    }
}