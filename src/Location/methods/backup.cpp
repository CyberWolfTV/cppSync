#include "../Location.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <regex>
#include <algorithm>

#include "../../helper_functions/helper_functions.hpp"

namespace fs = std::filesystem;

#define PAIR std::pair<const std::string, std::string>


void move_old_versions(const fs::path& file_name, int old_versions);


void Location::backup(){
    compare_all_for_backup();

    for(Location& loc : this->backup_locations){
        // it may help to put every kind of change in a separate loop
        // created loop
        for(const std::string& i: loc.changes.created){
            if(loc.is_in_scope(i)){
                fs::path target_parent = fs::path(loc.path) / fs::path(i);
                fs::create_directories(target_parent.parent_path());
                fs::copy_file({path / fs::path(i)}, {loc.path / fs::path(i)});
            }
        }

        // moved loop
        for(const PAIR& i: loc.changes.moved){
            // from i.first to i.second
            if(loc.is_in_scope(i.first) && loc.is_in_scope(i.second)){
                fs::path first = fs::canonical(loc.path / fs::path(i.first));
                fs::create_directories(loc.path / fs::path(i.second).parent_path());
                fs::path second = fs::canonical(loc.path / fs::path(i.second).parent_path());
                fs::rename(first, second / fs::path(i.second).filename());
            } else if(!loc.is_in_scope(i.first) && loc.is_in_scope(i.second)){
                // handle like created
                fs::path target_parent = fs::path(loc.path) / fs::path(i.second);
                fs::create_directories(target_parent.parent_path());
                fs::copy_file({path / fs::path(i.first)}, {loc.path / fs::path(i.second)});
            } else{
                // handle like deleted
                int old_versions = this->tree.nodes[0].get_node_config_ptr(fs::path(i.first))->old_versions;
                move_old_versions({loc.path / fs::path(i.first)}, old_versions);
            }
        }

        // changed loop
        for(const std::string& i: loc.changes.changed){
            if(loc.is_in_scope(i)){
                int old_versions = loc.tree.nodes[0].get_node_config_ptr(fs::path(i))->old_versions;
                move_old_versions((loc.path / fs::path(i)), old_versions);
                fs::copy_file((path / fs::path(i)), (loc.path / fs::path(i)));
            }
        }

        // deleted loop
        for(const std::string& i: loc.changes.deleted){
            if(loc.is_in_scope(i)){
                int old_versions = loc.tree.nodes[0].get_node_config_ptr(fs::path(i))->old_versions;
                move_old_versions({loc.path / fs::path(i)}, old_versions);
            }
        }
    }

    save_new_states();
}


void Location::save_new_states(){
    for(Location& loc: backup_locations){
        json backed_up_hashes;
        for(PAIR i: file_hashes){
            if(loc.is_in_scope(i.first)){
                backed_up_hashes.addpair(i.first, i.second);
            }
        }
        fs::path file_path = fs::path(loc.path) / fs::path(".cppSync/hashes/" + DATE_TIME);
        std::ofstream file_with_hashes(file_path);
        file_with_hashes << backed_up_hashes.get() << std::endl;
        file_with_hashes.close();
    }
}


void Location::compare_all_for_backup(){
    std::string state;
    for(const fs::directory_entry& entry : fs::directory_iterator(fs::path(path / "/.cppSync/hashes"))){
        state = entry.path();
        break;
    }

    for(Location& loc: backup_locations){
        // get most recent states of the backup location
        std::string loc_state;
        for(const fs::directory_entry& entry: fs::directory_iterator(fs::path(loc.path / "/.cppSync/hashes"))){
            loc_state = entry.path();
            break;
        }

        bool initial_state = false;
        if(loc_state.empty()){
            loc.get_hashes();
            fs::rename(fs::path(loc.path / "/.cppSync/hashes/" / fs::path(DATE_TIME)), fs::path(loc.path / "/.cppSync/hashes/initial_state"));
            loc_state = loc.path / "/.cppSync/hashes/initial_state";
            initial_state = true;
        }

        // compare the main and the loc states here
        loc.compare(state, loc_state);

        if(initial_state){
            fs::remove(fs::path(loc_state));
        }
    }
}


void move_old_versions(const fs::path& file_name, int old_versions){
    // move every file [. + filename + .bak-XXX] one up
    // -> [. + filename + .bak-(XXX+1)]
    // -> so the new file can just be copied to the destination
    if(!fs::is_regular_file(file_name)){
        return;
    }
    std::cout << old_versions;

    const fs::path old_path = fs::current_path();
    fs::current_path(file_name.parent_path());

    const fs::path name = file_name.filename();
    const std::string name_str = name.c_str();

    const std::string pattern_str = "\\./." + name_str + "\\.bak-[0-9][0-9][0-9]";
    const std::regex pattern = std::regex(pattern_str);

    std::vector<fs::path> old_version_files;
    for(fs::path const& dir_entry: std::filesystem::recursive_directory_iterator{fs::path(".")}){
        if(fs::is_directory(dir_entry)){
            continue;
        }
        if (std::regex_match(dir_entry.c_str(), pattern)){
               old_version_files.emplace_back(dir_entry);
        }
    }
    std::sort(old_version_files.rbegin(), old_version_files.rend()); // sorts reversed (9, 8, ...)

    while(!old_version_files.empty()){
        // there can be max old_versions (int) .bak-XXX files, make sure teh others get removed:
        std::string file = old_version_files[0].c_str();
        int version_num = stoi(file.substr(file.find_last_of('-')+1));
        if(version_num < old_versions){
            break;
        }
        fs::remove(old_version_files[0]);
        old_version_files.erase(old_version_files.begin());
    }

    for(fs::path const& old_version: old_version_files){
        // increment number + rename
        std::string old_version_str = old_version.c_str();
        char str[4];
        snprintf(str, 4, "%03d", stoi(old_version_str.substr(old_version_str.find_last_of('-')+1)) + 1);
        std::string new_name_str = "." + name_str + ".bak-" + str;
        fs::rename(old_version, fs::path(new_name_str));
    }

    if(old_versions == 0) {
        fs::remove(name);
    } else {
        std::string new_name = "." + name_str + ".bak-001";
        fs::rename(name, fs::path(new_name));
    }

    fs::current_path(old_path);
}
