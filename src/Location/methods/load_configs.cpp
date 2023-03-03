#include "../Location.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


void Location::load_configs(){
    std::cout << "Loading configuration files..." << std::endl;

    configs.whitelist = configurations::parse_list_file(path + "/.cppSync/configs/whitelist.txt");
    configs.blacklist = configurations::parse_list_file(path + "/.cppSync/configs/blacklist.txt");
    std::vector<std::string> raw_backup_locations = configurations::parse_list_file(path + "/.cppSync/configs/backup_locations.txt");
    for(const std::string& loc: raw_backup_locations){
        Location location(loc);
        configs.backup_locations.push_back(location);
    }
}


std::vector<std::string> Location::configurations::parse_list_file(const std::string& file_path){
    std::fstream whitelist_file;
    whitelist_file.open(file_path, std::ios::in);
    if(!whitelist_file.is_open()){
        std::cerr << "Couldn't open " + file_path << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> items;
    std::string line;
    while(getline(whitelist_file, line)){
        //remove leading and trailing spaces (https://stackoverflow.com/a/21815483/19808734)
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::bind1st(std::not_equal_to<char>(), ' ')));
        line.erase(std::find_if(line.rbegin(), line.rend(), std::bind1st(std::not_equal_to<char>(), ' ')).base(), line.end());

        if(line[0] != '#' && !line.empty()){
            items.push_back(line);
        }
    }
    return items;
}
