#include "helper_functions.hpp"

#include <string>
#include <map>


std::map<std::string, std::string> json_to_map(std::string json){
    std::string string, key, value;
    std::map<std::string, std::string> map;

    bool still_string;
    bool is_key = false;

    for(unsigned long long i = 0; i < json.length(); i++){
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
                map.insert(std::pair<std::string, std::string>(decode(key), value));
                key = "";
                value = "";
            }
        }
    }
    return map;
}


void json::addpair(const std::string& key, const std::string& value){
    json_object += R"(")";
    json_object += encode(&key);
    json_object += R"(": ")";
    json_object += value;
    json_object += R"(", )";
}


std::string json::get(){
    std::string data = json_object;
    data.erase(data.size() -2);
    data = '{' + data + '}';
    return data;
}
