#include <string>
#include <map>
#include <iostream>
#include "MyJSON.h"
#include "functions.h"

namespace my{
// private variables
std::string json_object;
int i2 = 0;

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



    void importJsonObject_to_map(std::string str, std::map<std::string, std::string> *map){
        std::string path;
        std::string checksum;

        for (auto i = 0; i < str.length(); i++){
            path = "";
            checksum = "";
            if(str[i] == '"'){
                i++;
                // get path
                for (int i2 = i; i2 < str.length();i2++){
                    if (str[i2] != '"'){
                    path += str[i2];
                    } else {
                        i2 = str.length();
                    }  
                }
                i += 4;
                i += path.length();
                
                //get value
                for (int i2 = i; i2 < str.length(); i2++){

                    if (str[i2] != '"'){
                    checksum += str[i2];
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
                i += checksum.length();
                
                //put stuff into map
                map->operator[](decode(path)) = checksum;
            }
        }
        return;
    }
}
