#pragma once

#include <vector>
#include <string>


namespace my{
    class Tree{
    private:
        /*
         * Node is a nested class which represents directories or files.
         */
        class Node{
        public:
            std::string name;
            bool is_file; // 1 = file, 0 = directory
            std::string checksum = NULL;

        // Constructors
            /*
             * For dirs: set is_file = 0, checksum = "" or NULL
             */
            Node(std::string arg_name, std::vector<std::vector<std::string>> arg_edges);

            /*
             * For files: set is_file = 1, checksum = arg_checksum, ...
             */
            Node(std::string arg_name, std::string arg_checksum, std::vector<std::vector<std::string>> arg_edges);

        // Methods:
            /*
             * Tells u if an edge is part of the node.
             */
            bool is_in_node(std::vector<std::string> edge);

            /*
             * Add and remove edges:
             */
            void remove_edge(std::vector<std::string> edge);
            void add_edge(std::vector<std::string> edge);

        private:
            /*
             * All the edges:
             * Edge: [source, dest]
             */
            std::vector<std::vector<std::string>> edges;
        };

    public:
    // Constructors
        //Tree();

        /*
         * This vector represents the graph.
         */
        std::vector<my::Tree::Node> tree;

        /*
         * This function does provide the functionality to turn the
         * list [no matter if its a black- or a whitelist] into
         * a tree.
         * It will call:
         *      is_in_tree()
         *      split_path() 
         */
        void list_to_tree(std::vector<std::string>);

    private:
        /*
         * This function returns a bool, telling u wether a node is
         * part of the tree.
         */
        bool is_in_tree(std::string);

        /*
         * Splits paths into nodes and returns them as tree
         * -> NOT as Tree instance, just as tree!
         * checksum = "" as default
         */
        std::vector<my::Tree::Node> split_path(std::string path, std::string checksum = "");
    };
}