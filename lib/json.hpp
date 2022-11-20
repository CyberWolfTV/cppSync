#pragma once

#include <string>
#include <map>


namespace my{
// encoding / decoding
    std::string encode(std::string str);
    std::string decode(std::string str);
    // kinda url-en-/decoding for json
    
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
