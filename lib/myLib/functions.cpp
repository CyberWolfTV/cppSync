#include <string>
#include <iostream>
#include <map>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


namespace my{

// datetime
// https://stackoverflow.com/a/10467633/19808734
std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

std::string encode(std::string str){
    std::string encodedString;
    
    for (int i = 0; i < str.length(); i++){
            if (str[i] == ':'){
                encodedString += "%3A";
            }else if(str[i] == '\\'){
                encodedString += "%5C";
            }else if(str[i] == ','){
                encodedString += "%2C";
            }else if(str[i] == '"'){
                encodedString += "%22";
            }else if(str[i] == '{'){
                encodedString += "%7B";
            }else if(str[i] == '}'){
                encodedString += "%7D";
            }else if(str[i] == '%'){
                encodedString += "%25";
            }else if(str[i] == ' '){
                encodedString += "%20";
            }else if(str[i] == '+'){
                encodedString += "%2B";
            }else if(str[i] == ']'){
                encodedString += "%5B";
            }else if(str[i] == ']'){
                encodedString += "%5D";
            }else{
            encodedString += str[i];
            }
    }
    return encodedString;
 }


std::string decode(std::string str){
    std::string decodedString;
    
    for (int i = 0; i < str.length(); i++){
        if (str[i] == '%'){
            i++;
            if (str[i] == '3' && str[i+1] == 'A'){
                decodedString += ':';
            }else if(str[i] == '5' && str[i+1] == 'C'){
                decodedString += '\\';
            }else if(str[i] == '2' && str[i+1] == 'C'){
                decodedString += ',';
            }else if(str[i] == '2' && str[i+1] == '2'){
                decodedString += '"';
            }else if(str[i] == '7' && str[i+1] == 'B'){
                decodedString += '{';
            }else if(str[i] == '7' && str[i+1] == 'D'){
                decodedString += '}';
            }else if(str[i] == '2' && str[i+1] == '5'){
                decodedString += '%';
            }else if(str[i] == '2' && str[i+1] == '0'){
                decodedString += ' ';
            }else if(str[i] == '2' && str[i+1] == 'B'){
                decodedString += '+';
            }else if(str[i] == '5' && str[i+1] == 'B'){
                decodedString += '[';
            }else if(str[i] == '5' && str[i+1] == 'D'){
                decodedString += ']';
            }
            i++;
        }
        else {
            decodedString += str[i];
        }
    }
    return decodedString;
}


int ask(std::string question){
    std::cout << question;
    std::string input;
    std::cin >> input;

    if(input == "n" or input == "N"){
        return 0;
    }else if(input == "y" or input == "Y"){
        return 1;
    }else{
        return ask(question);
    }
}

std::string get_name(std::string tempname){
    if(!fs::is_directory(tempname)){
        std::cout << "Enter the directoryname: ";
        std::cin >> tempname;
        return get_name(tempname);
    }
    return tempname;
}


bool is_inited(){
    try{
        std::string oldpath = fs::current_path();
        std::string newpath = oldpath + "/.cppSync/hashes";
        fs::current_path(newpath);
        fs::current_path(oldpath);
        return true;
    } catch (std::experimental::filesystem::v1::__cxx11::filesystem_error& e){
        return false;
    }
}


}
