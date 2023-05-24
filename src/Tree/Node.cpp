#include "Node.hpp"


Node::Node(const fs::path& path, Node* parent, Configs* configs){
    this->path = fs::path(path);
    this->parent = parent;
    this->config = configs->get_node_config_ptr(this->path);
}
