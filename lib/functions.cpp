#include "functions.hpp"

#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;



// datetime
// https://stackoverflow.com/a/10467633/19808734
std::string my::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

namespace my{
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
}

bool my::ask(std::string question){
    std::cout << question;
    std::string input;
    std::cin >> input;

    if(input == "n" or input == "N"){
        return false;
    }else if(input == "y" or input == "Y"){
        return true;
    }else{
        return ask(question);
    }
}

std::string my::get_name(std::string tempname){
    if(!fs::is_directory(tempname)){
        std::cout << "Enter the directoryname: ";
        std::cin >> tempname;
        return get_name(tempname);
    }
    return tempname;
}


bool my::is_inited(){
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


void my::help(){
    std::cout << "backup [Option/-s] $Name \n\nOptions:" << std::endl;
    std::cout << "--hash                  -> Just hashes all the files and saves the hashes in the .change/hashes directory." << std::endl;
    std::cout << "-i  / --init            -> Creates the .changes directory in the target directory. In this" << std::endl;
    std::cout << "                           directory will informations, outputs and configurations be stored." << std::endl;
    std::cout << "-c  / --compare         -> Compares the hashes of 2 .change files of ur choice." << std::endl;
    std::cout << "-cd / --compare-default -> Compares the current state with the last one." << std::endl;
    std::cout << "-fd / --find-duplicates -> Shows u all files in the directory which exists more than once." << std::endl;
    std::cout << "-nq / --no-questions    -> Does not ask any questions, u can use the script in scripts then." << std::endl;
    std::cout << "                           This will force compare-default." << std::endl;
    std::cout << "-b  / --backup          -> Creates a backup on the selected location." << std::endl;
    std::cout << "--configure             -> Pops up vim with the config file.." << std::endl;
    std::cout << "-h  / --help            -> Shows this information." << std::endl;
    exit(EXIT_SUCCESS);
    return;
}


std::multimap<std::string, std::string> my::reverse_map(std::map<std::string, std::string> *map){
    std::multimap<std::string, std::string> multimap;
    for(auto i = map->begin(); i != map->end(); i++){
        multimap.insert(std::pair<std::string, std::string>(i->second, i->first));
    } 
}
