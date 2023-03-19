#include "../Location.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

#include "../../helper_functions/helper_functions.hpp"

namespace fs = std::filesystem;

#define PAIR std::pair<const std::string, std::string>


void Location::backup(){
    compare_all_for_backup();

    for(auto & loc : configs.backup_locations){
        // it may helps to put every kind of change in a separate loop
        // created loop
        for(const std::string& i: loc.changes.created){
            if(loc.is_in_scope(i)){
                fs::path target_parent = fs::path(loc.path) / fs::path(i);
                fs::create_directories(target_parent.parent_path());
                fs::copy_file({path + '/' + i}, {loc.path + '/' + i});
            }
        }

        // moved loop
        for(const PAIR& i: loc.changes.moved){
            // from i.first to i.second
            if(loc.is_in_scope(i.first) && loc.is_in_scope(i.second)){
                fs::rename({loc.path + '/' + i.first}, {loc.path + '/' + i.second});
            } else if(!loc.is_in_scope(i.first) && loc.is_in_scope(i.second)){
                fs::path target_parent = fs::path(loc.path) / fs::path(i.second);
                fs::create_directories(target_parent.parent_path());
                fs::copy_file({path + '/' + i.first}, {loc.path + '/' + i.second});
            } else{
                // TODO i.first -> {'.' + i.first + '.bak-XXX'}
            }
        }

        // changed loop
        for(const std::string& i: loc.changes.changed){
            if(loc.is_in_scope(i)){
                // TODO i.first -> {'.' + i.first + '.bak-XXX'}

                fs::copy_file({path + '/' + i}, {loc.path + '/' + i});
            }
        }

        // deleted loop
        for(const std::string& i: loc.changes.changed){
            if(loc.is_in_scope(i)){
                // TODO i.first -> {'.' + i.first + '.bak-XXX'}
            }
        }
    }

    save_new_states();
}


void Location::save_new_states(){
    for(auto & loc: configs.backup_locations){
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


void Location::compare_all_for_backup() {
    std::string state;
    for(const auto & entry : fs::directory_iterator(fs::path(path + "/.cppSync/hashes"))){
        state = entry.path();
        break;
    }

    for (auto &loc: configs.backup_locations) {
        // get most recent states of the backup location
        std::string loc_state;
        for (const auto &entry: fs::directory_iterator(fs::path(loc.path + "/.cppSync/hashes"))) {
            loc_state = entry.path();
            break;
        }

        bool initial_state = false;
        if(loc_state.empty()){
            loc.get_hashes();
            fs::rename(fs::path(loc.path + "/.cppSync/hashes/" + DATE_TIME), fs::path(loc.path + "/.cppSync/hashes/initial_state"));
            loc_state = loc.path + "/.cppSync/hashes/initial_state";

            initial_state = true;
        }

        // compare the main and the loc states here
        loc.compare(state, loc_state);

        if(initial_state){
            fs::remove(fs::path(loc_state));
        }
    }
}
