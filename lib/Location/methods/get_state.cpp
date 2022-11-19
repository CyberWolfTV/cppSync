#include "../Location.hpp"
#include "../../json.hpp"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


std::map<std::string, std::string> my::Location::get_state(std::string path){
    std::fstream input_file(path);
    input_file.open("path", std::ios::out);
    if (!input_file.is_open()) {
        std::cerr << "could not open file " << path << std::endl;
        std::cerr << "[In: " << fs::current_path() << "]" << std::endl;
        exit(EXIT_FAILURE);
    }
    auto stringstream = std::ostringstream{};
    stringstream << input_file.rdbuf();
    std::string json = stringstream.str();
    input_file.close();

    return json_to_map(json);
}