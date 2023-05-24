#include "../Configs.hpp"

#include <iostream>


std::map<std::string, std::vector<std::string>> split_into_nodes(const std::vector<std::string>& lines, const fs::path& path);
std::vector<std::string> get_keys(const std::string& raw_keys);
Node_config get_node_config(const std::vector<std::string>& value);


void Configs::load_node_configs(const fs::path& path){
    std::vector<std::string> lines = get_clean_lines(path / ".cppSync/configs/.config");
    std::map<std::string, std::vector<std::string>> nodes = split_into_nodes(lines, path / ".cppSync/configs/.config");
    for(const std::pair<std::string, std::vector<std::string>> node: nodes){
        std::vector<std::string> keys = get_keys(node.first);
        this->actual_configs.emplace_back(get_node_config(node.second));
        for(const std::string& key: keys){
            this->node_configs[fs::path(key)] = &this->actual_configs[this->actual_configs.size()-1];
        }
    }
}


std::map<std::string, std::vector<std::string>> split_into_nodes(const std::vector<std::string>& lines, const fs::path& path){
    std::map<std::string, std::vector<std::string>> nodes;
    unsigned long line_count = lines.size();
    for(unsigned long i = 0; i < line_count; i++){
        std::string key;
        std::vector<std::string> value;
        if(lines[i][0] == '['){
            do{
                key += lines[i];
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
        nodes[key] = value;
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


Node_config get_node_config(const std::vector<std::string>& value){
    Node_config config{};
    for(const std::string& v: value){
        unsigned long len = v.size();
        if(v.substr(0, 11) == "old_versions"){
            config.old_versions = std::stoi(v.substr(len-4, len-2));
        }
    }
    return config;
}
