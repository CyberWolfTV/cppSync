#include "../Location.hpp"
#include "../../json.hpp"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


std::map<std::string, std::string> my::Location::get_state(std::string path, std::string file_name){
    std::string oldpath = fs::current_path();
    fs::current_path(path);

    auto stringstream = std::ostringstream{};
    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cerr << "could not open file " << path + "/" + file_name << std::endl;;
        exit(EXIT_FAILURE);
    }
    stringstream << input_file.rdbuf();
    std::string json_of_choice = stringstream.str();
    input_file.close();

    fs::current_path(oldpath);

    // #TODO rewrite json-parser -> return map directly
    std::map<std::string, std::string> map;
    importJsonObject_to_map(json_of_choice, &map);
    return map;
}