#pragma once

#include <string>
#include <map>

namespace my{
    std::string currentDateTime(); // returns datetime

    bool ask(std::string question);
    // question? [y/n] -> returns true / false

    std::string get_name(std::string tempname);
    bool is_inited();

    void help(); // prints help text and exits the program

    std::multimap<std::string, std::string> reverse_map(std::map<std::string, std::string> *map);
    /*
     * The function takes a normal map:
     * map[key] = value
     * -> keys are unique and values not
     * it returns a multimap like:
     * multimap[value] = key
     */
}
