#pragma once

#include <string>
#include <map>


namespace my{
// create json
    class MyJSON{
    private:
        std::string json_object;
        
    public:
        void addpair(std::string key, std::string value);
        std::string get();
    };


// import json
    std::map<std::string, std::string> json_to_map(std::string json);
    /*
     * Takes json string, return map.
     * Keys have to be unique!
     * Correct:
     *      "key":"value"
     * Wrong:
     *      'key':'value'
     *       key :'value'
     *      'key': value
     *      ...
     */
}
