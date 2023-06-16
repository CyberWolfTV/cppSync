#include "../Configs.hpp"

#include <iostream>
#include <algorithm>
#include <stack>


std::vector<std::pair<std::string, NodeConfig>> split_into_nodes(const std::vector<std::string>& lines, const fs::path& path);
std::vector<std::string> get_keys(const std::string& raw_keys);
NodeConfig values_to_node_configs(const std::vector<std::string>& value);
std::vector<std::string> sort_keys_by_depth(const std::vector<std::string>& keys_unsorted);
void apply_config_to_nodes(const fs::path& path, const NodeConfig& config, RootNode* root);


void Configs::load_node_configs(RootNode* root){
    std::vector<std::string> lines = get_clean_lines(root->path / ".cppSync/configs/.config");
    std::vector<std::pair<std::string, NodeConfig>> nodes = split_into_nodes(lines, root->path / ".cppSync/configs/.config");
    for(const std::pair<std::string, NodeConfig>& node: nodes){
        apply_config_to_nodes(fs::path(node.first), node.second, root);
    }
}


std::vector<std::pair<std::string, NodeConfig>> split_into_nodes(const std::vector<std::string>& lines, const fs::path& path){
    std::map<std::string, NodeConfig> nodes_unsorted;
    std::vector<std::string> keys;
    unsigned long line_count = lines.size();
    for(unsigned long i = 0; i < line_count; i++){
        std::string raw_keys;
        std::vector<std::string> value;
        if(lines[i][0] == '['){
            do{
                raw_keys += lines[i];
                i++;
            }while(lines[i][lines[i].size()-1] != ']');
        }
        else{
            std::cerr << "The configfile " + path.string() + " is broken." << std::endl;
            exit(EXIT_FAILURE);
        }
        while(lines[i][0] != '[' && i < lines.size()){
            value.emplace_back(lines[i]);
            i++;
        }
        for(const std::string& key: get_keys(raw_keys)){
            nodes_unsorted[key] = values_to_node_configs(value);
            keys.emplace_back(key);
        }
    }
    std::vector<std::pair<std::string, NodeConfig>> nodes;
    for(const std::string& key: sort_keys_by_depth(keys)){
        std::pair<std::string, NodeConfig> node;
        node.first = key;
        node.second = nodes_unsorted[key];
        nodes.emplace_back(node);
    }
    return nodes;
}


std::vector<std::string> get_keys(const std::string& raw_keys){
    unsigned long raw_keys_size = raw_keys.size()-1;
    std::vector<std::string> keys;
    for(unsigned long i = 1; i < raw_keys_size; i++){
        if(raw_keys[i] == '"' || raw_keys[i] == '\''){
            i++;
            std::string key;
            for(; i < raw_keys_size; i++){
                if((raw_keys[i] == '"' || raw_keys[i] == '\'') && raw_keys[i-1] != '\\'){
                    break;
                }
                key += raw_keys[i];
            }
            keys.emplace_back(key);
        }
    }
    return keys;
}


NodeConfig values_to_node_configs(const std::vector<std::string>& value){
    NodeConfig config{};
    for(const std::string& v: value){
        unsigned long len = v.size();
        if(v.substr(0, 11) == "old_versions"){
            config.old_versions = std::stoi(v.substr(len-4, len-2));
        }
    }
    return config;
}


std::vector<std::string> sort_keys_by_depth(const std::vector<std::string>& keys_unsorted){
    std::vector<std::string> keys_sorted;
    std::map<unsigned long, std::vector<std::string>> sorting;
    for(const std::string& i: keys_unsorted){
        unsigned long depth = std::count_if( i.begin(), i.end(), []( char c ){return c =='/';});
        sorting[depth].emplace_back(i);
    }
    for(const std::pair<unsigned long, std::vector<std::string>> i: sorting){
        for(const std::string& j: i.second){
            keys_sorted.emplace_back(j);
        }
    }
    return keys_sorted;
}


void apply_config_to_nodes(const fs::path& path, const NodeConfig& config, RootNode* root){
    std::vector<fs::path> split_path = std::vector(path.begin(),path.end());
    Node* current_node = root->childs[split_path[1]];
    for(unsigned long i = 2; i < split_path.size(); i++){
        current_node = current_node->childs[split_path[i]];
    }

    std::stack<Node*> nodes;
    nodes.emplace(current_node);
    while(!nodes.empty()){
        current_node = nodes.top();
        nodes.pop();
        for(const std::pair<const fs::path, Node*>& i: current_node->childs){
            nodes.emplace(i.second);
        }
        current_node->config = config;
    }
}
