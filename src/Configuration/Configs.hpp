#ifndef CPPSYNC_CONFIGS_HPP
#define CPPSYNC_CONFIGS_HPP

#include <vector>
#include <string>
#include <map>
#include <filesystem>

#include "../Location/Location.hpp"
#include "../Tree/Node.hpp"

namespace fs = std::filesystem;


class Configs{
public:
    void load_location_config(const fs::path& path);
    static void load_node_configs(RootNode* root);

private:
    static std::vector<std::string> parse_list_file(const fs::path& file_path);
    static std::vector<std::string> get_clean_lines(const fs::path& path);
};


#endif
