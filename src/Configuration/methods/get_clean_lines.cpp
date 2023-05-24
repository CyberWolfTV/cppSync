#include "../Configs.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>


std::string remove_leading_tailing_spaces_tabs(const std::string& line);


std::vector<std::string> Configs::get_clean_lines(const fs::path& path){
    std::fstream file;
    file.open(path, std::ios::in);
    if(!file.is_open()){
        std::cerr << "Couldn't open " + path.string() << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> lines;
    std::string line;
    while(getline(file, line)){
        line = remove_leading_tailing_spaces_tabs(line);

        std::string clean_line;
        if(line[0] == '#'){continue;}
        clean_line += line[0];
        for(unsigned long i = 1; i < line.size(); i++){
            if(line[i] == '#' && line[i-1] != '\\'){
                break;
            }
            clean_line += line[i];
        }

        lines.emplace_back(clean_line);
    }
    return lines;
}


std::string remove_leading_tailing_spaces_tabs(const std::string& line){
    unsigned long beginning = line.find_first_not_of("  \t");
    unsigned long ending = line.find_last_not_of(" \t") + 1;
    if(ending == std::string::npos || beginning == std::string::npos){
        return "#";
    }
    return line.substr(beginning, ending);
}
