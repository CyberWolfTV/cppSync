#include "../Location.hpp"

#include <string>
#include <map>

#include "../../helper_functions/helper_functions.hpp"


void Location::compare(const std::string& source, const std::string& target){
    // source -> from main instance (newer one)
    // target -> from backup locations (older one)
    std::map<std::string, std::string> source_states = get_state(source);
    std::map<std::string, std::string> target_states = get_state(target);

    // Let's create a map with all paths, so we can take a look on how
    // they changed.
    std::map<std::string, bool> all_paths;
    for(auto & target_state : target_states){
        all_paths[target_state.first] = true;
    }
    for(auto & source_state : source_states){
        all_paths[source_state.first] = true;
    }

    /*
     * In the following for-loop the paths will be sorted in different vectors/maps.
     * Algorithm explained:
     * changed [vector]:
     *  1. Both maps have a hash for a given part.
     *  2. These hashes differ.
     *
     * moved_created [map]:
     *  1. The newer state (source) has a hash for the given path.
     *  2. The older state (target) does not have a hash for the given path.
     *
     * moved_deleted [map]:
     *  1. The older state (target) has a hash for the given path.
     *  2. The newer state (source) does not have a hash for the given path.
     */
    std::string target_hash;
    std::string source_hash;
    std::map<std::string, std::string> moved_deleted;
    std::map<std::string, std::string> moved_created;

    for(auto & all_path : all_paths){
        target_hash = target_states[all_path.first];
        source_hash = source_states[all_path.first];

        if(target_hash == source_hash){
            target_states.erase(all_path.first);
            source_states.erase(all_path.first);
            continue;
        }
        if(target_hash.empty()){
            moved_created[all_path.first] = source_hash;
            continue;
        }
        if(source_hash.empty()){
            moved_deleted[all_path.first] = target_hash;
            continue;
        }
        if(target_hash != source_hash){
            changes.changed.push_back(all_path.first);
            target_states.erase(all_path.first);
            source_states.erase(all_path.first);
            continue;
        }
    }
    bool found = false;
    for(auto & i : moved_created){
        for(auto & target_state : target_states){
            if(i.second == target_state.second){
                changes.moved[target_state.first] = i.first;
                found = true;
            }
        }
        if(!found){
            changes.created.emplace_back(i.first);
        }
        found = false;
    }

    for(auto & i : moved_deleted){
        for(auto & source_state : source_states){
            if(i.second == source_state.second){
                changes.moved[i.first] = source_state.first;
                found = true;
            }
        }
        if(!found){
            changes.deleted.push_back(i.first);
        }
        found = false;
    }
}
