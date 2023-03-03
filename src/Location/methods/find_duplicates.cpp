#include "../Location.hpp"

#include <iostream>
#include <fstream>
#include <map>

#define MULTIMAP_ITERATOR std::multimap<std::string, std::string>::iterator

std::multimap<std::string, std::string> reverse_map(std::map<std::string, std::string> *map);


void Location::find_duplicates(){
    std::multimap<std::string, std::string> map_of_hashes = reverse_map(&file_hashes);

    std::string result_file = ".cppSync/duplicates/" + DATE_TIME;
    std::ofstream duplicates(result_file);

    std::cout   << "--------------------------------------" << std::endl;
    std::cout                                               << std::endl;
    std::cout                                               << std::endl;
    std::cout   << "Every file in a block is the same."     << std::endl;
    std::cout                                               << std::endl;
    duplicates  << "# Every file in a block is the same."   << std::endl;
    duplicates                                              << std::endl;

    std::string old_hash;
    std::string new_hash;
    bool empty_line;
    for(auto i = map_of_hashes.begin(); i != map_of_hashes.end(); i++){
        new_hash = i->first;
        if(new_hash != old_hash){
            std::pair<MULTIMAP_ITERATOR, MULTIMAP_ITERATOR> result = map_of_hashes.equal_range(new_hash);
            long distance = std::distance(result.first, result.second);
            for(auto it = result.first; it != result.second; it++){
                if(distance > 1){
                    duplicates  << it->second << std::endl;
                    std::cout   << it->second << std::endl;
                    empty_line = true;
                }
            }
        }
        else if(empty_line){
            duplicates  << std::endl;
            std::cout   << std::endl;
            empty_line = false;
        }
        old_hash = new_hash;
    }
    std::string duplicates_file = path + ".changes/duplicates./" + DATE_TIME;
    std::cout                                                       << std::endl;
    std::cout << "Which files are duplicates is also saved in:"     << std::endl;
    std::cout << R"(  ")" << duplicates_file << R"(")"              << std::endl;
}


std::multimap<std::string, std::string> reverse_map(std::map<std::string, std::string> *map){
    std::multimap<std::string, std::string> multimap;
    for(auto & i : *map){
        multimap.insert(std::pair<std::string, std::string>(i.second, i.first));
    }
    return multimap;
}
