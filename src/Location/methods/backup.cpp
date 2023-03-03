#include "../Location.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

#include "../../helper_functions/helper_functions.hpp"

namespace fs = std::filesystem;


std::vector<Location> get_active_locs(const std::vector<Location>& locs);

#define PAIR std::pair<const std::string, std::string>


void Location::backup(){
    std::vector<Location> available_backup_locations = get_active_locs(configs.backup_locations);
    json backed_up_hashes;
    for(auto & loc : available_backup_locations){
        for(PAIR i: file_hashes){
            if(loc.is_in_scope(i.first)){
                fs::path source = fs::path(path) / fs::path(i.first);
                fs::path target_parent = fs::path(loc.path) / fs::path(i.first).parent_path();
                fs::create_directories(target_parent);
                fs::copy(source, target_parent, fs::copy_options::overwrite_existing);

                backed_up_hashes.addpair(i.first, i.second);
            }
        }
        fs::path file_path = fs::path(loc.path) / fs::path(".cppSync/hashes/" + DATE_TIME);
        std::ofstream file_with_hashes(file_path);
        file_with_hashes << backed_up_hashes.get() << std::endl;
        file_with_hashes.close();
    }
}



std::vector<Location> get_active_locs(const std::vector<Location>& locs){
    std::vector<Location> available_locs;
    for(const auto & loc : locs){
        if(fs::is_directory(loc.path)){
            available_locs.emplace_back(loc);
        } else{
            std::cout << R"(Backup location ")" << loc.path << R"(" is NOT available.)" << std::endl;
        }
    }
    return available_locs;
}
