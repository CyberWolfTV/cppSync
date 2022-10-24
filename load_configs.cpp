#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "load_configs.hpp"

namespace my{
    void loadconfigs(
        std::string *name,
        std::vector<std::string> *backup_locations,
        int *old_versions,
        bool *whitelist_or_blacklist,
        std::vector<std::string> *list){
        
        std::fstream config_file;
        std::string filename = *name + "/.cppSync/.config";
        config_file.open(filename, std::ios::in);

        if (config_file.is_open()){

            std::string line;
            while(getline(config_file, line)){
                if(line[0] == '#'){
                    // its a comment
                }
                else if(line[1] == 'o'){
                    // its locations, so pushback
                    line.erase(0, 9);
                    backup_locations->push_back(line);
                }
                else if(line[5] == 't'){
                    if(line[10] == 'b'){
                        *whitelist_or_blacklist = false;
                    }
                    else if(line[10] == 'w'){
                        *whitelist_or_blacklist = true;
                    }
                }
                else if(line[5] == 'i'){
                    // list item
                    line.erase(0,10);
                    list->push_back(line);
                }
                else if(line[0] == 'b'){
                    char number[3];
                    number[0] = line[4];
                    number[1] = line[5];
                    number[2] = line[6];
                    *old_versions = atoi(number);
                }
            }
        } else{
            std::cerr << "COULDNT OPEN THE CONFIG FILE!" << std::endl;
        }
        
    }
}