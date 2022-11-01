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
        void find_duplicates(); // run ALWAYS after get_hashes!
        void backup();
        void compare();
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

        void rec_hashing();
        bool is_in_scope();
    };
}