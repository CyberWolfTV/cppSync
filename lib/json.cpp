#include "json.hpp"
#include "functions.hpp"

namespace my{
// private variables
std::string json_object;

// public functions

void MyJSON::addpair(std::string path, std::string checksum){
    json_object += "\"";
    json_object += encode(path);
    json_object += "\": \"";
    json_object += checksum;
    json_object += "\", ";
}

std::string MyJSON::get(){
    json_object.erase(json_object.size() -2);
    json_object = '{' + json_object + '}';
    return json_object;
}


std::multimap<std::string, std::string> importJsonObject_to_multimap(std::string str){

    std::string key;
    std::string value;
    std::multimap<std::string, std::string> myMap;

    for (auto i = 0; i < str.length(); i++){

        std::string key = "";
        std::string value = "";
        
        if(str[i] == '"'){
            i++;
            // get key
            for (int i2 = i; i2 < str.length();i2++){
                if (str[i2] != '"'){
                key += str[i2];
                } else {
                    i2 = str.length();
                }  
            }
            i += 4;
            i += key.length();
            
            //get value
            for (int i2 = i; i2 < str.length(); i2++){

                if (str[i2] != '"'){
                value += str[i2];
                }
                else {
                    i2 ++;

                    if(str[i2] == '}'){
                        i = str.length();
                    }
                    i2++;
                    i2 = str.length();
                }
            }
            i++;
            i += value.length();
            

            //put stuff into map
            myMap.insert(std::pair<std::string, std::string>(value, decode(key)));
            }
        }
        return myMap;
    }
}


std::map<std::string, std::string> my::json_to_map(std::string json){
    std::string string, key, value;
    std::map<std::string, std::string> map;

    bool still_string;
    bool is_key = false;

    for(long long i = 0; i < json.length(); i++){
        if(json[i] == '"'){
            i++;
            still_string = true;
            string = "";
            while(still_string){
                if(json[i] == '"'){
                    still_string = false;
                    is_key = ~is_key;
                    i += string.length() + 1;
                }else{
                    string += json[i];
                }
            }

            if(is_key){
                key = string;
            } else{
                value = string;
                map[decode(key)] = decode(value);
                key = "";
                value = "";
            }
        }
    }
    return map;
}