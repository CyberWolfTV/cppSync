#ifndef CPPSYNC_NODE_HPP
#define CPPSYNC_NODE_HPP


#include <vector>
#include <filesystem>
#include <map>

#include "../Configuration/Configs.hpp"

namespace fs = std::filesystem;


class Node{
public:
    Node(const fs::path& path, Node* parent, Configs* configs);

    fs::path path;

    Node* parent;
    std::map<fs::path, Node*> childs;

    Node_config* config;
};


#endif
