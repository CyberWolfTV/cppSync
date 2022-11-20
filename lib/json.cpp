#include "json.hpp"


std::string my::encode(std::string str){
    std::string encodedString;
    
    for (int i = 0; i < str.length(); i++){
        switch(str[i]){
            case(':'):
                encodedString += "%A";
                break;
            case('\\'):
                encodedString += "%B";
                break;
            case(','):
                encodedString += "%C";
                break;
            case('"'):
                encodedString += "%D";
                break;
            case('{'):
                encodedString += "%E";
                break;
            case('}'):
                encodedString += "%F";
                break;
            case('%'):
                encodedString += "%G";
                break;
            case(' '):
                encodedString += "%H";
                break;
            case('+'):
                encodedString += "%I";
                break;
            case('['):
                encodedString += "%J";
                break;
            case(']'):
                encodedString += "%K";
                break;
            default:
                encodedString += str[i];
        }
    }
    return encodedString;
 }


 std::string my::decode(std::string str){
    std::string decodedString;
    
    for (int i = 0; i < str.length(); i++){
        if (str[i] == '%'){
            i++;
            switch(str[i]){
                case('A'):
                    decodedString += ':';
                    break;
                case('B'):
                    decodedString += '\\';
                    break;
                case('C'):
                    decodedString += ',';
                    break;
                case('D'):
                    decodedString += '"';
                    break;
                case('E'):
                    decodedString += '{';
                    break;
                case('F'):
                    decodedString += '}';
                    break;
                case('G'):
                    decodedString += '%';
                    break;
                case('H'):
                    decodedString += ' ';
                    break;
                case('I'):
                    decodedString += '+';
                    break;
                case('J'):
                    decodedString += '[';
                    break;
                case('K'):
                    decodedString += ']';
                    break;
            }
            i++;
        }else {
            decodedString += str[i];
        }
    }
    return decodedString;
}


void my::MyJSON::addpair(std::string key, std::string value){
    json_object += "\"";
    json_object += encode(key);
    json_object += "\": \"";
    json_object += value;
    json_object += "\", ";
    return;
}

std::string my::MyJSON::get(){
    json_object.erase(json_object.size() -2);
    json_object = '{' + json_object + '}';
    return json_object;
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
                map.insert(std::pair<std::string, std::string>(decode(key), value));
                key = "";
                value = "";
            }
        }
    }
    return map;
}