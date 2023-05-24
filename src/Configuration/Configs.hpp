#ifndef CPPSYNC_CONFIGS_HPP
#define CPPSYNC_CONFIGS_HPP


#include <vector>
#include <string>
#include <map>
#include <filesystem>

#include "../Location/Location.hpp"

namespace fs = std::filesystem;


struct Location_config{
    std::vector<std::string> backup_locs;
    std::vector<std::string> whitelist;
    std::vector<std::string> blacklist;
};


struct Node_config{
    bool is_git_repo;
    int old_versions;
};


class Configs{
public:
    Location_config location_config;

    void load_location_config(const fs::path& path);
    void load_node_configs(const fs::path& path);

    Node_config* get_node_config_ptr(const std::string& path);

    static std::vector<std::string> get_clean_lines(const fs::path& path);

private:
    std::vector<Node_config> actual_configs;
    std::map<fs::path, Node_config*> node_configs;
};


#endif
