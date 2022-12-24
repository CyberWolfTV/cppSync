#include <string>
#include <vector>

namespace my{
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

        /*
         * Splits paths into nodes and returns them as tree
         * -> NOT as Tree instance, just as tree!
         */
        std::vector<my::Node> path_to_nodes(std::string path);
        std::vector<my::Node> path_to_nodes(std::string path, std::string checksum);
    private:
        my::Node to_node(std::string name, std::string checksum);
        my::Node to_node(std::string name);
    };
}