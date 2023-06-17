#include "../Location.hpp"


void Location::Tree::add_path_to_tree(const fs::path& file_path){
    Node* current = &this->nodes[0];
    std::vector<fs::path> split_path = std::vector(file_path.begin(),file_path.end());
    for(unsigned long i = 1; i < split_path.size(); i++){
        if(current->childs.count(split_path[i]) != 0){
            Node node = Node(split_path[i], current);
            this->nodes.emplace_back(node);
            current->childs[split_path[i]] = &this->nodes[this->nodes.size()-1];
        }
        current = current->childs[split_path[i]];
    }
}
