#pragma once

#include <vector>
#include <string>
#include <map>

namespace my{
    class Location{
    public:
        // Constructors:
        Location(std::string arg_name, std::string arg_datetime);

        // methods
        void compare(); 
        // thats the compare function which is getting user input and passing it
        // to the real compare function (which is private)
        void find_duplicates(); // run ALWAYS after get_hashes!
        void backup();
        void get_hashes();

        // Variables
        std::string name;
        // name of the parent directory
        // or the absolute path, lets go with the absolute path..
        std::string datetime;
        std::vector<my::Location> backup_locations;
        std::map<std::string, std::string> map_with_hashes;
        // has all the paths (keys) & checksums (values)
        //  -> checksums can be the same, paths are unique

        // config variables
        bool location_type; // maybe remove #TODO
        int old_versions;
        // How many .bakXXX files should get saved
        bool whitelist_or_blacklist;
        std::vector<std::string> list; 

    private:
        // methods
        void loadconfig();

        // the "real" compare function
        void compare(std::string source, std::string target);
        void print_compared();
        void get_state(std::string source_location, std::string target_location);
        std::map<std::string, std::string> source_states;
        std::map<std::string, std::string> target_states;

        void rec_hashing(std::string name);
        bool is_in_scope(std::string dir_entry);

        // Variables from the compare function:
        // (moved includes renamed...)
        // these (from main instance) are only used for the user-compare and
        // *maybe* when we pull changes from a backup location
        std::vector<std::string> created;
        std::vector<std::string> changed; 
        std::vector<std::string> deleted; 
        std::map<std::string, std::string> moved;
    };
}