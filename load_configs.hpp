#pragma once

#include <vector>
#include <string>
#include <map>

namespace my{
    void loadconfigs(
        std::string *name,
        std::vector<std::string> *backup_locations,
        int *old_versions,
        bool *whitelist_or_blacklist,
        std::vector<std::string> *list
    );
}
