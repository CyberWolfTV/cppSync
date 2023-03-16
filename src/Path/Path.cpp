#include "Path.hpp"

#include <sstream>


Path::Path(std::string arg_path){
    path = std::move(arg_path);
}

std::string Path::append(const std::string& path_to_append){
    std::string place_holder;
    return place_holder;
}

fs::path Path::to_fs_path(){
    return {(path)};
}


std::vector<std::string> Path::split() const{
    std::vector<std::string> split_path;
    std::string part;
    std::stringstream ss(path);
    while (getline(ss, part, '/')){
        split_path.push_back(part);
    }
    return split_path;
}
