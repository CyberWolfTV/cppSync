#include "../Location.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void my::Location::loadconfig(){
    config_file.open(".cppSync/.config", std::ios::in);
    if (config_file.is_open()){

        std::string line;
        while(getline(config_file, line)){
            if(line[0] == '#'){
                // its a comment
            }
            else if(line[1] == 'o'){
                
                line.erase(0, 9);
                // create an object with constructor
                backup_locations.push_back(Location(line, datetime));
            }
            else if(line[5] == 't'){
                if(line[10] == 'b'){
                    whitelist_or_blacklist = false;
                }
                else if(line[10] == 'w'){
                    whitelist_or_blacklist = true;
                }
            }
            else if(line[5] == 'i'){
                // list item
                line.erase(0,10);
                list.push_back(line);
            }
            else if(line[0] == 'b'){
                char number[3];
                number[0] = line[4];
                number[1] = line[5];
                number[2] = line[6];
                old_versions = atoi(number);
            }
        }
    } else{
        std::cerr << "COULDNT OPEN THE CONFIG FILE!" << std::endl;
    }
}
