#include <vector>
#include <string>
#include <map>

namespace my{
    class Location{
    public:
        // Constructors:
        Location();

        // methods
        void compare();
        void find_duplicates();
        void backup();
        void compare();
        void rec_hashing();

        // config variables
        std::string name;
        // name of the parent directory
        bool location_type; // maybe remove #TODO
        int old_versions;
        // How many .bakXX files should get saved
        std::vector<std::string> list; 
        // first element defines wether white or blacklist

        // other variables
        std::vector<my::Location> backup_locations;
        std::map<std::string, std::string> map_with_hashes;
        // has all the paths (keys) & checksums (values)
        //  -> checksums can be the same, paths are unique


    private:
        // methods
        void loadconfig();
    };
}