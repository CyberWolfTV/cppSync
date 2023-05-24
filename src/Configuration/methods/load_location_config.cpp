#include "../Configs.hpp"

#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> parse_list_file(const std::string& file_path);


void Configs::load_location_config(const fs::path& path){
    this->location_config.whitelist = parse_list_file(path / ".cppSync/configs/whitelist.txt");
    this->location_config.blacklist = parse_list_file(path / ".cppSync/configs/blacklist.txt");
    this->location_config.backup_locs = parse_list_file(path / ".cppSync/configs/backup_locations.txt");
}


std::vector<std::string> parse_list_file(const fs::path& file_path){
    std::vector<std::string> items = Configs::get_clean_lines(file_path);
    for(std::string & item : items){
        if((item[0] == '\'' || item[item.size()-1] == '\'') || (item[0] == '\"' || item[item.size()-1] == '\"')) {
            item = item.substr(1, item.size() - 2);
        } else{
            std::cerr << "Configfile : " + file_path.string() + " is not properly formatted!" << std::endl;
        }
    }
    return items;
}
