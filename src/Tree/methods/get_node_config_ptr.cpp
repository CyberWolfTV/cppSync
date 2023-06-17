#include "../Node.hpp"

#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

NodeConfig* Node::get_node_config_ptr(const fs::path& path_to_node){
    Node* node = this;
    while(node != nullptr) {
        node = node->parent;
    }
    std::vector<fs::path> split_path = std::vector(path_to_node.begin(),path_to_node.end());
    for(unsigned long i = 1; i < split_path.size(); i++){
        node = node->childs[split_path[i]];
    }
    return &node->config;
}
