#include "Location.hpp"
#include "../functions.hpp"

#include <iostream>
#include <vector>

/*
 * Constructor for the main instance:
 */
my::Location::Location(std::string arg_name, std::map<std::string, bool> arg_options){
    datetime = my::currentDateTime();
    options = arg_options;

    name = arg_name;
    location_type = "main";

    // init
    if(!my::is_inited()){
        std::cout << name << " was not inited." << std::endl;
        if(my::ask("Would u like to init this directory [y/n]: ")){
            init();
        } else{
            exit(EXIT_FAILURE);
        }
    }

    loadconfig();

    // configure
    if(options["configure"]){
        for(int i = 0; i < backup_locations.size(); i++){
            std::cout << "[" << std::to_string(i) << "] " << backup_locations[i].name << std::endl;
        }

        while(true){
            std::string str_choice;
            std::cin >> str_choice;
            int choice = atoi(str_choice.c_str());
            if(choice >= 0 && choice < backup_locations.size()){
                std::string command = "vim \"" + backup_locations[choice].name + "/.cppSync/.config\"";
                const char * c = command.c_str();
                std::system(c);
                break;
            }
        }
    }
}


/*
 * Constructor for the backup locations:
 */
my::Location::Location(std::string arg_name, std::string arg_datetime){
    name = arg_name;
    location_type = "backup";
    datetime = arg_datetime;

    // init
    if(!my::is_inited()){
        std::cout << name << " was not inited." << std::endl;
        if(my::ask("Would u like to init this directory [y/n]: ")){
            init();
        } else{
            exit(EXIT_FAILURE);
        }
    }
    
    loadconfig();
}