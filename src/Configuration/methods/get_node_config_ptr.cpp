#include "../Configs.hpp"

#include <vector>
#include <string>

#include "../../Path/Path.hpp"

#define PAIR std::pair<const fs::path, Node_config*>


Node_config *Configs::get_node_config_ptr(const std::string& path){
    Path node_path = Path(path);
    std::vector<std::string> split_path = node_path.split();

    Node_config* result = nullptr;
    unsigned long max_depth = 0, depth = 0;
    for(PAIR& i: node_configs){
        Path config_path = Path(i.first.string());
        std::vector<std::string> split_conf_path = config_path.split();

        if(split_conf_path.size() > split_path.size()){
            continue;
        }

        for(unsigned long j = 0; j < split_conf_path.size(); j++){
            if(split_path[j] == split_conf_path[j]){
                depth++;
            } else{
                depth = 0;
                break;
            }
        }
        if(depth > max_depth){
            result = i.second;
        }
    }
    return result;
}
