#include "../Location.hpp"

#include <fstream>
#include <filesystem>
#include <stack>
#include <iostream>

#include "../../helper_functions/helper_functions.hpp"
#include "../../hash_functions/sha256.hpp"

namespace fs = std::filesystem;


void Location::get_hashes(){
    fs::current_path(fs::path(this->path));

    json json_hashes;
    std::stack<fs::path> abc_directories;
    abc_directories.emplace(".");
    while(!abc_directories.empty()){
        fs::path dir = abc_directories.top();
        abc_directories.pop();
        for (auto const& dir_entry : fs::directory_iterator{dir}){
            if(fs::is_regular_file(dir_entry.path()) && is_in_scope(dir_entry.path())){
                std::string hash = sha256(dir_entry.path().string());
                std::string file_path = dir_entry.path().string();
                file_hashes.insert(std::pair<std::string, std::string>(file_path, hash));
                json_hashes.addpair(file_path, hash);
            }
            else if(fs::is_directory(dir_entry.path())){
                abc_directories.emplace(dir_entry.path());
            }
            else{
                // TODO: catch other filetypes
                std::cout << "bad filetype, pls catch" << std::endl;
            }
        }
    }
    std::ofstream file_with_hashes(path / "/.cppSync/hashes/" / fs::path(DATE_TIME));
    file_with_hashes << json_hashes.get() << std::endl;
    file_with_hashes.close();
}
