#include "../Node.hpp"

#include <stack>
#include <filesystem>

namespace fs = std::filesystem;


void apply_git_to_childs(Node* git_repo_parent);


void RootNode::detect_git_repos(){
    std::stack<Node*> nodes;
    nodes.emplace(this);
    while(!nodes.empty()){
        Node* current_node = nodes.top();
        nodes.pop();

        if(current_node->childs.count(fs::path(".git")) != 0){
            if(current_node->childs[fs::path(".git")]->childs.count(fs::path("HEAD")) != 0){
                apply_git_to_childs(current_node);
                continue;
            }
        }

        for(std::pair<fs::path, Node*> node: current_node->childs){
            nodes.push(node.second);
        }
    }
}


void apply_git_to_childs(Node* git_repo_parent){
    std::stack<Node*> nodes;
    nodes.emplace(git_repo_parent);
    while(!nodes.empty()){
        Node* current_node = nodes.top();
        nodes.pop();
        for(const std::pair<const fs::path, Node*>& i: current_node->childs){
            nodes.emplace(i.second);
        }
        current_node->config.is_git_repo = true;
    }
}
