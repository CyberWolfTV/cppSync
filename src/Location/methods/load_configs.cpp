#include "../Location.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;


void remove_inactive_locs(std::vector<std::string> *locations);


void Location::load_configs(bool is_main_location){
    std::cout << "Loading configuration files..." << std::endl;

    configs.whitelist = configurations::parse_list_file(path + "/.cppSync/configs/whitelist.txt");
    configs.blacklist = configurations::parse_list_file(path + "/.cppSync/configs/blacklist.txt");

    if(is_main_location) {
        std::vector<std::string> raw_backup_locations = configurations::parse_list_file(path + "/.cppSync/configs/backup_locations.txt");
        remove_inactive_locs(&raw_backup_locations);
        for (const std::string &loc: raw_backup_locations) {
            std::cout << loc << std::endl;
            Location location(loc);
            location.load_configs(false);
            // not a real recursion, gets called with is_main_location = true ONLY
            configs.backup_locations.push_back(location);
        }
    }
}


std::vector<std::string> Location::configurations::parse_list_file(const std::string& file_path){
    std::fstream file;
    file.open(file_path, std::ios::in);
    if(!file.is_open()){
        std::cerr << "Couldn't open " + file_path << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> items;
    std::string line;
    while(getline(file, line)){
        unsigned long beginning = line.find_first_not_of("  \t");
        if(beginning == std::string::npos){
            continue;
        }
        unsigned long ending = line.find_last_not_of(" \t") + 1;
        if(ending == std::string::npos){
            continue;
        }
        line = line.substr(beginning, ending);

        if(line[0] != '#'){
            items.push_back(line);
        }
    }
    return items;
}


void remove_inactive_locs(std::vector<std::string> *locations){
    for(long i = 0; i < locations->size(); i++){
        if(!fs::is_directory(fs::path(locations->operator[](i)))){
            locations->erase(locations->begin()+i);
            std::cout << R"(Backup location ")" << locations->operator[](i) << R"(" is NOT available.)" << std::endl;
        }
    }
}
