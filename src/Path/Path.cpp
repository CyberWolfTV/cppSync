#include "Path.hpp"


std::string Path::append(const std::string& path_to_append){
    std::string place_holder;
    return place_holder;
}

fs::path Path::to_fs_path(){
    return {(path)};
}


std::vector<std::string> Path::split(){
    std::vector<std::string> split_path;

    unsigned long beginning = 0;
    std::string part;
    for(unsigned long i = 0; i < path.length(); i++){
        if(path[i] == '\\' | path[i] == '/'){
            part = path.substr(beginning, i);
            if(part == "."){
                beginning = i + 1;
                continue;
            }
            split_path.emplace_back(part);
        }
        beginning = i + 1;
    }

    return split_path;
}