#include "Node.hpp"


Node::Node(const fs::path& path, Node* parent){
    this->path = fs::path(path);
    this->parent = parent;
    this->config.is_git_repo = false;
}
