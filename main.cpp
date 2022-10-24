#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cstring>

/*
Include em if needed
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sstream>
*/

#include "lib/myLib/functions.hpp"

#include "backup.hpp"
#include "compare.hpp"
#include "find_duplicates.hpp"
#include "help.hpp"
#include "init.hpp"
#include "recHashing.hpp"
#include "load_configs.hpp"


int main(int argc, char *argv[]){
    // Variables
    std::string datetime = my::currentDateTime();
    std::string name;
    std::map<std::string, std::string> MapOfHashes; // check if its needed, maybe use it in get_hashes only

    // config variables
    std::vector<std::string> backup_locations;
    int old_versions;
    bool whitelist_or_blacklist;
    std::vector<std::string> list;

    // what changed (pass to compare & backup)
    std::vector<std::string> created;
    std::vector<std::string> changed;
    std::vector<std::string> deleted;
    std::map<std::string, std::string> moved; // map<newPath, oldPath> moved;

    // map for args
    std::map<std::string, int> options;

    
    // ARGS
    options["compare"] = 0;
    options["init"] = 0;
    options["backup"] = 0;
    options["find-duplicates"] = 0;
    options["hash"] = 0;
    options["configure"] = 0;
    options["no-questions"] = 0;
    options["compare-default"] = 0;
    

    for(int i = 1; i < argc; i++){

        std::string argument = argv[i];
        
        if(argument == "-c" || argument == "--compare"){
            options["compare"] = 1;

        }
        else if(argument == "-cd" || argument == "--compare-default"){
            options["compare"] = 1;
            options["compare-default"] = 1;
        }
        else if(argument == "-h" || argument == "--help"){
            my::help();
        }
        else if(argument == "-i" || argument == "--init"){
            options["init"] = 1;
        }
        else if(argument == "-nq" || argument == "--no-questions"){
            // TODO make the script running in other scripts)
            options["no-questions"] = 1;
            options["compare-default"] = 1;
        }
        else if(argument == "-b" || argument == "--backup"){
            // TODO write backup function(-s)
            options["backup"] = 1;
        }
        else if(argument == "-fd" || argument == "--find-duplicates"){
            // TODO write function(-s)
            options["find-duplicates"] = 1;
        }
        else if(argument == "--hash"){
            // TODO write function(-s)
            options["hash"] = 1;
        }
        else if(argument == "--configure"){
            // TODO write function(-s)
            options["configure"] = 1;
        }
        else{
            name = argument;
        }
    }
    
    // verify directory exists, if not -> ask for the correct 1
    name = my::get_name(name);
    

    // init should be first!
    if(options["init"] == 1){
        my::init(&name);
    }

    // verify directory was inited
    if(!my::is_inited(&name)){
        std::cout << "This directory was not inited, run the same command and add --init." << std::endl;
        exit(EXIT_FAILURE);
    }


    // configure
    if(options["configure"] == 1){
        std::string command = "vim \"" + name + "/.cppSync/.config\"";
        const char * c = command.c_str();
        std::system(c);
    }


    // parse config file
    my::loadconfigs(&name, &backup_locations, &old_versions, &whitelist_or_blacklist, &list);
    
    // Hashing the Directory $name
    if(options["hash"] == 1 || options["compare"] == 1 || options["find-duplicates"] == 1){
        my::get_hashes(&name, &datetime, &MapOfHashes);
    }

    // find duplicates
    if(options["find-duplicates"] == 1){
        my::find_duplicates(&name, &datetime);
    }

    // compare
    
    if(options["compare"] == 1){
        my::compare(&options, &name, &datetime, &created, &changed, &deleted, &moved);
    }
    



    // backup
    if(options["backup"] == 1 && options["compare-default"] == 1){
        //pass the what changes variables to backup function
        // my::backup(all_what_changed_vars);
    }
    else if(options["backup"] == 1 && options["compare"] == 0){
        // use compare function normally and then do it like above
        options["compare-default"] = 1;
        my::compare(&options, &name, &datetime, &created, &changed, &deleted, &moved);
        // my::backup(all_what_changed_vars);
    }
    else if(options["backup"] == 1 && options["compare"] == 1){
        // create new what changed vars, set default true
        std::vector<std::string> alt_created;
        std::vector<std::string> alt_changed;
        std::vector<std::string> alt_deleted;
        std::map<std::string, std::string> alt_moved; // map<newPath, oldPath> moved;

        options["compare-default"] = 1;

        my::compare(&options, &name, &datetime, &alt_created, &alt_changed, &alt_deleted, &alt_moved);
        // my::backup(all_alt_what_changed_vars);
    }

    return 0;
}



/*
 *      Compiling:
 *
 *      -lstdc++fs [if idk: -lc++fs]
 *      lib/myLib/sha256.cpp
 *      lib/myLib/functions.cpp 
 *      lib/myLib/MyJSON.cpp
 *      help.cpp
 *      backup.cpp
 *      compare.cpp
 *      init.cpp
 *      find_duplicates.cpp
 *      recHashing.cpp
 *      load_configs.cpp
 *
 *      g++ main.cpp backup.cp load_configs.cpp compare.cpp init.cpp find_duplicates.cpp recHashing.cpp -lstdc++fs lib/myLib/sha256.cpp lib/myLib/MyJSON.cpp lib/myLib/functions.cpp -o cppSync.out
 *      g++ main.cpp backup.cp load_configs.cpp compare.cpp init.cpp find_duplicates.cpp recHashing.cpp -lstdc++fs lib/myLib/sha256.cpp lib/myLib/MyJSON.cpp lib/myLib/functions.cpp -o ~/Clipboard/cppSync
 *
 *      alias build="g++ main.cpp backup.cpp load_configs.cpp compare.cpp init.cpp find_duplicates.cpp recHashing.cpp help.cpp -lstdc++fs lib/myLib/sha256.cpp lib/myLib/MyJSON.cpp lib/myLib/functions.cpp -o ~/Clipboard/cppSync"
 */