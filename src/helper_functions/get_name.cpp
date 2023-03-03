#include "helper_functions.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


std::string get_name(std::string name){
    while(true){
        if(fs::is_directory(name)){
            return name;
        }
        if(name == "exit" || name == "e"){
            std::cout << "exit or e means exit...." << std::endl;
            exit(EXIT_FAILURE);
        }
        std::cout << "Enter the directory name: ";
        std::cin >> name;
    }
}