#include "Location.hpp"

#include <iostream>
#include <string>
#include <filesystem>

#include "../helper_functions/helper_functions.hpp"

namespace fs = std::filesystem;


Location::Location(const std::string& path){
    this->path = canonical(fs::path(path));
    bool is_inited = fs::is_directory(this->path / ".cppSync");

    if(!is_inited){
        std::cout << path << " is not inited yet." << std::endl;
        if(ask("Would u like to init this directory [Y/n]: ", 'y')){
            init();
        } else{
            std::cerr << "A directory must be inited." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    this->configs.load_location_config(this->path);
    this->configs.load_node_configs(this->path);

    this->tree.nodes.emplace_back(this->path, nullptr, &this->configs);
}
