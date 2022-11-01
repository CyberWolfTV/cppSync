#include "../Location.hpp"
#include "../../lib/myLib/MyJSON.hpp"

#include <string>
#include <iostream>
#include <map>
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

void my::Location::find_duplicates(){
    auto stringstream = std::ostringstream{};

    std::string recent_hashes = ".cppSync/hashes/" + datetime;
    std::ifstream input_file(recent_hashes);
    if (!input_file.is_open()) {
        std::cerr << "could not open file " << file_and_path << std::endl;;
        exit(EXIT_FAILURE);
    }

    stringstream << input_file.rdbuf();
    std::string newest_hashes = stringstream.str();

    std::multimap<std::string, std::string> map_of_hashes = importJsonObject_to_multimap(newest_hashes);

    std::string result_file = ".cppSync/dulplicates/" + datetime;
    std::ofstream duplicates(result_file);

    duplicates << "# Every path of a block points towards a duplicate file\n" << std::endl;

    std::string oldHash;
    typedef std::multimap<std::string, std::string>::iterator multi_map_iterator;

    int empy_lines;

    for(auto i = map_of_hashes.begin(); i != map_of_hashes.end(); i++){

        std::string newKey = i->first;     
        if(newKey != oldHash){
            typedef std::multimap<std::string, std::string>::iterator multi_map_iterator;
            std::pair<multi_map_iterator, multi_map_iterator> result = map_of_hashes.equal_range(newKey);
            // Iterate over the range
            for (multi_map_iterator it = result.first; it != result.second; it++){
                        
                // show how many values there are for the hash 
                int distance = std::distance(result.first, result.second);
                if(distance > 1){
                    duplicates << it->second << std::endl;
                    std::cout << it->second << std::endl; 
                    empy_lines = 1;
                }
            }
        } else{
            if(empy_lines == 1){
                duplicates << "\n";
                std::cout << "\n";
                empy_lines = 0;
            }
        }
            oldHash = newKey;
    }
    std::cout << "\nWhich files are duplicates is also saved in .changes/duplicates." << std::endl;
}