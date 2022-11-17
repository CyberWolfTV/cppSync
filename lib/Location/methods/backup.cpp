#include "../Location.hpp"

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


void my::Location::backup(){

        /*// test if backup locations are available (usb mounted etc.)
        for(auto i = backup_locations->begin(); i != backup_locations->end(); i++){
            if(!fs::is_directory(*i)){
                    i->erase();
                    std::cout << "Backup location \"" << *i << "\" is not available." << std::endl;
            } else{
                // backup...
            }
        }
        
    }*/
    return;

}