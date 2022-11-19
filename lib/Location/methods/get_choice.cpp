#include "../Location.hpp"

#include <iostream>
#include <cstring>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


std::string my::Location::get_choice(){
    int files_len = 0;
    std::map<int, std::string> files;
    for(const auto& i : fs::recursive_directory_iterator(".cppSync/hashes/")){
        std::string filename = i.path().string();
        std::cout << "[" << files_len << "] " << filename.erase(0, 16) << std::endl;
        files[files_len] = filename;
        files_len++;
    }

    std::string test_choice;
    std::cin >> test_choice;
    int choice = atoi(test_choice.c_str());
    
    if(choice > files_len + 1 || choice < 0){
        return get_choice();
    } else{
        return files[choice];
    }
}