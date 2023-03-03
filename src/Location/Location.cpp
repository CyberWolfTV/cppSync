#include "Location.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

#include "../helper_functions/helper_functions.hpp"


namespace fs = std::filesystem;


Location::Location(std::string arg_path){
    path = std::move(arg_path);

    if(!check_if_inited()){
        std::cout << path << " is not inited yet." << std::endl;
        if(ask("Would u like to init this directory [Y/n]: ", 'y')){
            init();
        } else{
            std::cerr << "A directory must be inited." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    load_configs();
}


bool Location::check_if_inited() const{
    return fs::is_directory(path + "/.cppSync");
}
