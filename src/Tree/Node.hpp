#ifndef CPPSYNC_NODE_HPP
#define CPPSYNC_NODE_HPP

#include <vector>
#include <filesystem>
#include <map>

#include "../Configuration/Configs.hpp"

namespace fs = std::filesystem;


struct NodeConfig{
    bool is_git_repo;
    int old_versions;
};


class Node{
public:
    Node(const fs::path& path, Node* parent, Configs* configs);

    fs::path path;
    NodeConfig config;
    Node* parent;
    std::map<fs::path, Node*> childs;

    NodeConfig* get_node_config_ptr(const fs::path& path_to_node);
    static NodeConfig* get_node_config_ptr(const fs::path& path_to_node, Node* node);
};


class RootNode: public Node{
public:
    void detect_git_repos();
    std::vector<Node*> get_leafs();
};

#endif
