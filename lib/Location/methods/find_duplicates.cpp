#include "../Location.hpp"
#include "../../json.hpp"
#include "../../functions.hpp"

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


void my::Location::find_duplicates(){
    std::multimap<std::string, std::string> map_of_hashes = reverse_map(&map_with_hashes);

    std::string result_file = ".cppSync/dulplicates/" + datetime;
    std::ofstream duplicates(result_file);

    duplicates << "# Every path of a block points towards a duplicate file\n" << std::endl;

    std::string oldHash;
    typedef std::multimap<std::string, std::string>::iterator multimap_iterator;

    int empy_lines;

    for(auto i = map_of_hashes.begin(); i != map_of_hashes.end(); i++){

        std::string newKey = i->first;     
        if(newKey != oldHash){
            std::pair<multimap_iterator, multimap_iterator> result = map_of_hashes.equal_range(newKey);
            // Iterate over the range
            for (multimap_iterator it = result.first; it != result.second; it++){
                        
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