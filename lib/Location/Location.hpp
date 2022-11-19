#pragma once

#include <vector>
#include <string>
#include <map>

namespace my{
    class Location{
    public:
    // Constructors:
        Location(std::string arg_name,
                 std::string arg_datetime,
                 std::map<std::string, bool> arg_options
                 );
        /* 
         * This is the standard constructor. 
         * It takes the following parameter
         *  name
         *  -> absolute path to the parent dir of .cppSync
         *  datetime
         *  -> datetime for all instances is defined in main.cpp
         *     as the time when starting the program
         *  options
         *  -> this is the map with args created in main.cpp
         */ 

    // Methods:
        void compare();
        /*
         * This function will be called when the user wants to compare
         * smth., for supplying the backup function we use the private 
         * function compare which takes the target and source state as
         * argument, (this function does also call the private one 
         * after it got the states the user wants to compare)
         *
         * TLDR; this function passes the users choice to the real compare
         * function
         *
         * PS: does not require recent hashes, can run without rec_hashing
         */ 
        
        void find_duplicates(); // run ALWAYS after get_hashes!
        void backup();
        /*
         * - Clears the vectors created by compare function.
         * - Loads latest states from backup locations and compares them
         *   with latest from the main instance.
         * - creates backup... TODO: write the internal stuff here...
         */

        void get_hashes();
        std::map<std::string, std::string> map_with_hashes;
        // has all the paths (keys) & checksums (values)
        //  -> checksums can be the same, paths are unique
        /*
         * get_hashes calls rec_hashing which fills map_with_hashes and 
         * then outputs the hashes in json format to the file datetime
         * -> uses MyJSON, sha256
         *
         * map_with_hashes
         * - actual state of the location
         * - map<paths, checksums> -> checksums != unique, paths are
         */

        // ask for which backup-loc then which state
        void restore(); 

        // Variables
        std::string name;
        // name of the parent directory
        // or the absolute path, lets go with the absolute path..
        std::string datetime;
        std::vector<my::Location> backup_locations;

        // config variables
        bool location_type; // maybe remove #TODO
        int old_versions;
        // How many .bakXXX files should get saved
        bool whitelist_or_blacklist;
        std::vector<std::string> list; 

    private:
        void loadconfig();
        /*
         * This functions parses the .config file.
         * -> output: backup_locations, old_versions,
         *            white_or_blacklist, list
         * -> gets called once in the constructor
         */

        void rec_hashing(std::string name);
        bool is_in_scope(std::string dir_entry);

        // the "real" compare function
        void compare(std::string source, std::string target);
        std::map<std::string, std::string> source_states;
        std::map<std::string, std::string> target_states;
        // Variables from the compare function:
        // (moved includes renamed...)
        // these (from main instance) are only used for the user-compare and
        // *maybe* when we pull changes from a backup location
        std::vector<std::string> created;
        std::vector<std::string> changed; 
        std::vector<std::string> deleted; 
        std::map<std::string, std::string> moved;
        void print_compared();  // prints changes + writes em to file

        std::map<std::string, bool> options;
        /*
         * Options from main.cpp, passed through constructor 
         */

        std::map<std::string, std::string> get_state(std::string path, std::string file_name);
        /*
         * takes path to states [/.../.cppSync/hashes], should work with relativ paths too
         * and the name of the file u want to load [without '/']
         * 
         * returns the state as map (not multimap)
         */

        std::string get_choice();
        /*
         * prints all names of the files in .cppSync/hashes/
         * asks which file the user wants
         * returns name of the file [without path to it]
         */
    };
}