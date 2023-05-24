#include "../Location.hpp"


void Location::Tree::add_path_to_tree(const fs::path& file_path, Configs* config){
    Node* current = &this->nodes[0];
    std::vector<fs::path> split_path = std::vector(file_path.begin(),file_path.end());
    if(current->childs.count(split_path[1]) == 0){
        this->nodes.emplace_back(split_path[0] / split_path[1], current, config);
        current->childs[split_path[1]] = &this->nodes[this->nodes.size()-1];
    }
    current = current->childs[split_path[1]];
    for(unsigned long i = 2; i <= split_path.size(); i++){
        if(current->childs.count(split_path[i]) == 0){
            this->nodes.emplace_back(current->path / split_path[i], current, config);
            current->childs[split_path[i]] = &this->nodes[this->nodes.size()-1];
        }
        current = current->childs[split_path[i]];
    }
}
