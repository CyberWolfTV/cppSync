#include "lib/Location/Location.hpp"
#include "lib/functions.hpp"

#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


int main(int argc, char *argv[]){
    std::string name;
    std::map<std::string, bool> options;

    
    // ARGS
    options["compare"] = false;
    options["backup"] = false;
    options["find-duplicates"] = false;
    options["hash"] = false;
    options["configure"] = false;
    options["no-questions"] = false;
    options["compare-default"] = false;
    

    for(int i = 1; i < argc; i++){
        std::string argument = argv[i];
        
        if(argument == "-c" || argument == "--compare"){
            options["compare"] = true;

        }
        else if(argument == "-cd" || argument == "--compare-default"){
            options["compare"] = true;
            options["compare-default"] = true;
        }
        else if(argument == "-h" || argument == "--help"){
            my::help();
        }
        else if(argument == "-nq" || argument == "--no-questions"){
            // TODO make the script running in other scripts)
            options["no-questions"] = true;
            options["compare-default"] = true;
        }
        else if(argument == "-b" || argument == "--backup"){
            // TODO write backup function(-s)
            options["backup"] = true;
        }
        else if(argument == "-fd" || argument == "--find-duplicates"){
            // TODO write function(-s)
            options["find-duplicates"] = true;
        }
        else if(argument == "--hash"){
            // TODO write function(-s)
            options["hash"] = true;
        }
        else if(argument == "--configure"){
            // TODO write function(-s)
            options["configure"] = true;
        }
        else{
            name = argument;
        }
    }
    
    // verify directory exists, if not -> ask for the correct 1
    name = my::get_name(name);
    name = fs::current_path().string() + "/" + name;

    // cd into name
    fs::current_path(name);

    



    /*
     * Im creating a Location Object, this one is the main instance.
     * That means this will be the original Folder u want to backup.
     * We are calling the methods of the instance here, they will 
     * call methods of the backup locations.
     */

    my::Location main_instance(name, options);

    // Hashing the Directory $name
    if(options["hash"] || options["find-duplicates"] || options["restore"]){
        main_instance.get_hashes();
    }

    if(options["find-duplicates"]){
        main_instance.find_duplicates();
    }

    if(options["compare"]){
        main_instance.compare();
    }

    if(options["backup"]){
        main_instance.backup();
    }
    


/*
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
*/
    return 0;
}



/*
 *      Compiling:
 *
 *      Main-Function:
 *          main.cpp      
 *      Flags for the compiler:
 *          -lstdc++fs [if idk: -lc++fs] -> filesystem iirc
 *      Location and methods:
 *          lib/Location/Location.cpp
 *          lib/Location/methods/backup.cpp
 *          lib/Location/methods/compare.cpp
 *          lib/Location/methods/find_duplicates.cpp
 *          lib/Location/methods/rec_hashing.cpp
 *          lib/Location/methods/loadconfig.cpp
 *          lib/Location/methods/restore.cpp
 *          lib/Location/methods/get_choice.cpp
 *          lib/Location/methods/get_state.cpp
 *          lib/Location/methods/init.cpp
 *      Other functions:
 *          lib/sha256.cpp
 *          lib/functions.cpp 
 *          lib/json.cpp
 *          
 *
 *      g++ main.cpp -lstdc++fs lib/Location/Location.cpp lib/Location/methods/backup.cpp lib/Location/methods/compare.cpp lib/Location/methods/find_duplicates.cpp lib/Location/methods/rec_hashing.cpp lib/Location/methods/loadconfig.cpp lib/Location/methods/restore.cpp lib/Location/methods/get_choice.cpp lib/Location/methods/init.cpp lib/Location/methods/get_state.cpp lib/sha256.cpp lib/functions.cpp lib/jsonN.cpp  -o cppSync.out
 *      g++ main.cpp -lstdc++fs lib/Location/Location.cpp lib/Location/methods/backup.cpp lib/Location/methods/compare.cpp lib/Location/methods/find_duplicates.cpp lib/Location/methods/rec_hashing.cpp lib/Location/methods/loadconfig.cpp lib/Location/methods/restore.cpp lib/Location/methods/get_choice.cpp lib/Location/methods/init.cpp lib/Location/methods/get_state.cpp lib/sha256.cpp lib/functions.cpp lib/json.cpp -o ~/Clipboard/cppSync
 *
 *      alias build="g++ main.cpp -lstdc++fs lib/Location/Location.cpp lib/Location/methods/backup.cpp lib/Location/methods/compare.cpp lib/Location/methods/find_duplicates.cpp lib/Location/methods/rec_hashing.cpp lib/Location/methods/loadconfig.cpp lib/Location/methods/restore.cpp lib/Location/methods/get_choice.cpp lib/Location/methods/get_state.cpp lib/Location/methods/init.cpp lib/sha256.cpp lib/functions.cpp lib/json.cpp -o ~/Clipboard/cppSync"
 */