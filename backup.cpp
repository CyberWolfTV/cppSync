#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


namespace my{

    void replace_main_dir_name(std::string *new_name, std::string *path, int *name_length){

    }

    void sync(std::vector<std::string> *created, 
        std::vector<std::string> *changed, 
        std::vector<std::string> *deleted, 
        std::map<std::string, std::string> *moved,
        std::string backup_location,
        int *old_versions,
        bool whitelist_or_blacklist,
        std::vector<std::string> *list){
        
        // changed (eziest)


    }

    void backup(
        std::vector<std::string> *created, 
        std::vector<std::string> *changed, 
        std::vector<std::string> *deleted, 
        std::map<std::string, std::string> *moved,
        std::vector<std::string> *backup_locations,
        int *old_versions,
        bool *whitelist_or_blacklist,
        std::vector<std::string> *list){

        // test if backup locations are available (usb mounted etc.)
        for(auto i = backup_locations->begin(); i != backup_locations->end(); i++){
            if(!fs::is_directory(*i)){
                    i->erase();
                    std::cout << "Backup location \"" << *i << "\" is not available." << std::endl;
            } else{
                    sync(created, changed, deleted, moved, *i, old_versions, *whitelist_or_blacklist, list);
            }
        }
        
    }

}