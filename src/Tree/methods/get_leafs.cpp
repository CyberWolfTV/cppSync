#include "../Node.hpp"

#include <stack>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


std::vector<Node*> RootNode::get_leafs(){
    std::vector<Node*> leafs;
    std::stack<Node*> nodes;
    nodes.emplace(this);
    while(!nodes.empty()){
        Node* current_node = nodes.top();
        nodes.pop();
        if(current_node->childs.empty()){
            leafs.emplace_back(current_node);
            continue;
        }
        for(std::pair<fs::path, Node*> node: current_node->childs){
            nodes.push(node.second);
        }
    }
}
