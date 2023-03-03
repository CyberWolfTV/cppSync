#include "helper_functions.hpp"

#include <string>
#include <iostream>
#include <filesystem>

#include "../Location/Location.hpp"

namespace fs = std::filesystem;


std::string get_choice(std::string const *path){
    fs::path path_to_states = *path + "/.cppSync/hashes";
    int file_number = 0;
    std::map<int, std::string> files;
    for(const auto& i : fs::directory_iterator(path_to_states)){
        std::string filename = i.path().string();
        std::cout << "[" << file_number << "] " << filename.erase(0, 16) << std::endl;
        files[file_number] = filename;
        file_number++;
    }

    while(true){
        int choice = get_int("Please choose one of the files:");
        if(choice <= file_number || choice >= 0) {
            return files[choice];
        }
    }
}


