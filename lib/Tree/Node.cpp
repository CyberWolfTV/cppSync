#include "Tree.hpp"


// Constructors
my::Tree::Node::Node(std::string arg_name, std::vector<std::vector<std::string>> arg_edges){
    name = arg_name;
    edges = arg_edges;
    is_file = false;
}

my::Tree::Node::Node(std::string arg_name, std::string arg_checksum, std::vector<std::vector<std::string>> arg_edges){
    name = arg_name;
    edges = arg_edges;
    checksum = arg_checksum;
    is_file = true;
}


// Methods
bool my::Tree::Node::is_in_node(std::vector<std::string> edge){
    
}

// remove and add edges
void remove_edge(std::vector<std::string> edge){
}
void add_edge(std::vector<std::string> edge){
}
