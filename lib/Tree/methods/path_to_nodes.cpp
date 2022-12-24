#include "../Tree.hpp"
#include "../Node.hpp"

#include <sstream>


std::vector<std::string> split_path(std::string path){
    std::stringstream test("this_is_a_test_string");
    std::string node;
    std::vector<std::string> nodes;

    while(std::getline(test, node, '/')){
    nodes.push_back(node);
    }
}

my::Node my::Node::to_node(std::string name, std::string checksum){
    std::vector<std::vector<std::string>> edges;
    my::Node node = my::Node(name, checksum, edges);
    return node;
}

my::Node my::Node::to_node(std::string name){

}


std::vector<my::Node> my::Node::path_to_nodes(std::string path){
    std::vector<std::string> raw_nodes = split_path(path);

    
}

std::vector<my::Node> my::Node::path_to_nodes(std::string path, std::string checksum){
    std::vector<std::string> raw_nodes = split_path(path);
}