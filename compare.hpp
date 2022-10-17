#pragma once

#include <map>
#include <vector>
#include <string>

namespace my{
    void compare(std::map<std::string, int> *options, std::string *name, std::string *datetime, std::vector<std::string> *created, std::vector<std::string> *changed, std::vector<std::string> *deleted,std::map<std::string, std::string> *moved);
}
