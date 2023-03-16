#include "../Location.hpp"

#include <string>
#include <vector>
#include <iostream>

#include "../../Path/Path.hpp"


bool Location::is_in_scope(std::string file_or_dir){
    Path file_or_dir_path = Path(std::move(file_or_dir));
    std::vector<std::string> split_path = file_or_dir_path.split();

    // exclude .cppSync
    if(split_path[1] == ".cppSync"){return false;}

    std::vector<std::string> split_list_entry;
    unsigned long max_black_depth = 0, black_depth = 0;
    for(const std::string& list_entry_string: configs.blacklist){
        Path list_entry = Path(list_entry_string);
        split_list_entry = list_entry.split();

        if(split_list_entry.size() > split_path.size()){
            continue;
        }

        for(unsigned long i = 0; i < split_list_entry.size(); i++){
            if(split_path[i] == split_list_entry[i]){
                black_depth++;
            } else{
                black_depth = 0;
                break;
            }
        }
        if(black_depth > max_black_depth){
            max_black_depth = black_depth;
        }
        black_depth = 0;
    }

    if(max_black_depth == 0){return true;}

    unsigned long max_white_depth = 0, white_depth = 0;
    for(const std::string& list_entry_string: configs.whitelist){
        Path list_entry = Path(list_entry_string);
        split_list_entry = list_entry.split();

        if(split_list_entry.size() > split_path.size()){
            continue;
        }

        for(unsigned long i = 0; i < split_list_entry.size(); i++){
            if(split_path[i] == split_list_entry[i]){
                white_depth++;
            } else{
                white_depth = 0;
                break;
            }
        }
        if(white_depth > max_white_depth){
            max_white_depth = white_depth;
        }
        white_depth = 0;
    }

    if(max_black_depth > max_white_depth){return false;}
    if(max_black_depth == max_white_depth){
        std::cerr << "There is a misconfiguration in this directory:"           << std::endl;
        std::cerr << path                                                       << std::endl;
        std::cerr << "The same Path is in the white- and the blacklist file."   << std::endl;
        exit(EXIT_FAILURE);
    }
    return true;
}
