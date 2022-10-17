#pragma once

#include <vector>
#include <string>
#include <map>

namespace my{
    void backup(
        std::vector<std::string> *created, 
        std::vector<std::string> *changed, 
        std::vector<std::string> *deleted, 
        std::map<std::string, std::string> *moved,
        std::vector<std::string> *backup_locations,
        int *old_versons,
        bool *whitelist_or_blacklist,
        std::vector<std::string> *list
    );
}
