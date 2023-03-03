#include "helper_functions.hpp"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;


std::map<std::string, std::string> get_state(const std::string& path){
    std::fstream input_file(path);
    input_file.open("path", std::ios::out);
    if (!input_file.is_open()) {
        std::cerr << "could not open file " << path << std::endl;
        std::cerr << "[In: " << fs::current_path() << "]" << std::endl;
        exit(EXIT_FAILURE);
    }
    auto string_stream = std::ostringstream{};
    string_stream << input_file.rdbuf();
    std::string json = string_stream.str();
    input_file.close();

    return json_to_map(json);
}