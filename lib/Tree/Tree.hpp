#pragma once

#include <vector>
#include <string>

#include "Node.hpp"


namespace my{
    class Tree{
    public:
        /*
         * This vector represents the graph.
         */
        std::vector<my::Node> tree;

        /*
         * This function does provide the functionality to turn the
         * list [no matter if its a black- or a whitelist] into
         * a tree.
         * It will call:
         *      is_in_tree()
         *      split_path() 
         */
        void list_to_tree(std::vector<std::string> list);

        /*
         * This function returns a bool, telling u wether a node is
         * part of the tree.
         */
        bool is_in_tree(my::Node node);
    };
}