#include "../Location.hpp"

#include <iostream>

#include "../../helper_functions/helper_functions.hpp"


void Location::configurations::configure(std::string loc_path){
    bool use_main_loc = ask("Do u want to configure this location?", 'y');
    if(!use_main_loc){
        for(int i = 0; i < backup_locations.size(); i++){
            std::cout << "[" << std::to_string(i) << "] " << backup_locations[i].path << std::endl;
        }
        while(true) {
            int choice = get_int("Location: ");
            if (choice >= 0 && choice < backup_locations.size()) {
                loc_path = backup_locations[choice].path;
                break;
            }
            std::cout << "The value must be between 0 and " << std::to_string(backup_locations.size()-1) << std::endl;
        }
    }

    bool edit;
    std::cout << "Edit configurations for the location:"                << std::endl;
    std::cout << loc_path                                               << std::endl;
    std::cout << "---------------------------------------------------"  << std::endl;
    std::cout                                                           << std::endl;

    loc_path = "    " + loc_path + ".cppSync/configs/";

    std::cout << "Edit how many versions of a file should be saved."    << std::endl;
    std::cout << "Current value: " << std::to_string(old_versions)  << std::endl;
    edit = ask("Do u want to edit this parameter? [n/Y] ", 'y');
    if(edit){
        old_versions = get_int("Please enter the new value: ");
    }
    std::cout << "---------------------------------------------------"  << std::endl;
    std::cout                                                           << std::endl;

    std::cout << "Edit this file to add and remove backup-locations:"   << std::endl;
    std::cout << loc_path << "backup_locations.txt"                     << std::endl;
    std::cout                                                           << std::endl;

    std::cout << "Edit this file to edit the whitelist:"                << std::endl;
    std::cout << loc_path << "whitelist.txt"                            << std::endl;
    std::cout                                                           << std::endl;

    std::cout << "Edit this file to edit the blacklist:"                << std::endl;
    std::cout << loc_path << "blacklist.txt"                            << std::endl;
    std::cout                                                           << std::endl;

    save_configs();
}

void Location::configurations::save_configs(){}
