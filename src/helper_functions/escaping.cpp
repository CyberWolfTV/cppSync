#include "helper_functions.hpp"

#include <string>


std::string encode(std::string const *str){
    std::string encodedString;
    for(char c : *str){
        switch(c){
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
                encodedString += c;
        }
    }
    return encodedString;
}


std::string decode(std::string str){
    std::string decodedString;
    for(int i = 0; i < str.length(); i++){
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
        }else {
            decodedString += str[i];
        }
    }
    return decodedString;
}