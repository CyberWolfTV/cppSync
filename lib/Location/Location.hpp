#pragma once

#include <vector>
#include <string>
#include <map>

namespace my{
    class Location{
    public:
    // Constructors:
        Location(std::string arg_name,
                 std::map<std::string, bool> arg_options
                 );
        /* 
         * This is the Constructor for the main instance. 
         * It takes the following parameter
         *  arg_name
         *  -> absolute path to the parent dir of .cppSync
         *  arg_options
         *  -> this is the map with args created in main.cpp
         * 
         * It will set DATETIME, it will also execute the functions
         * specified by the OPTIONS.
         * It will load the configs of the config file.
         */

        Location(std::string arg_name);
        /*
         * This is the Constructor for the backup locations.
         * arg_name
         *  -> absolute path to the parent dir of .cppSync
         * 
         * It will load the configs of the config file.
         */

    // Methods:
        void init();
        /*
         * creates directories + config file
         *
         * content of the config file will (probably)
         * depend on the location_type
         */

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
        static std::string DATETIME;
        std::vector<my::Location> backup_locations;

        // config variables
        std::string location_type; 
        // main or backup, used in init function
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

        static std::map<std::string, bool> OPTIONS;
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