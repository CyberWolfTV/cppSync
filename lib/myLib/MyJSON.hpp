#pragma once

#include <string>
#include <map>
#include <iostream>

namespace my{
    class MyJSON{
    private:
        std::string json_object;
        int i2;
        
    public:
    // creating json object
        void init();
        void addpair(std::string key, std::string value);
        void close();
        std::string get();
    };

    // functions for importing JSON
    void importJsonObject_to_map(std::string str, std::map<std::string, std::string> *map);
    std::multimap<std::string, std::string> importJsonObject_to_multimap(std::string str);
}
