#ifndef CPPSYNC_LOCATION_HPP
#define CPPSYNC_LOCATION_HPP

#include <string>
#include <vector>
#include <map>

#include "../Tree/Node.hpp"


struct arguments{
    std::string name;
    bool compare = false;
    bool backup = false;
    bool find_duplicates = false;
    bool hash = false;
    bool no_questions = false;
    bool compare_default = false;
};


struct LocationConfig{
    std::vector<std::string> backup_locs;
    std::vector<std::string> whitelist;
    std::vector<std::string> blacklist;
};


class Location {
public:
    LocationConfig config;
    fs::path path;
    inline static std::string DATE_TIME;
    inline static struct arguments args;

    LocationConfig configs;
    std::vector<Location> backup_locations;

    explicit Location(const std::string& path);

    void init() const;

    void get_hashes();
    bool is_in_scope(std::string file_or_dir);
    std::map<std::string, std::string> file_hashes;
    std::vector<std::string> directories;

    void find_duplicates();

    void compare(const std::string& source, const std::string& target);
    struct comp_changes{
        std::vector<std::string> created;
        std::vector<std::string> changed;
        std::vector<std::string> deleted;
        std::map<std::string, std::string> moved;
    } changes;

    void backup();
    void save_new_states();
    void compare_all_for_backup();

    void restore();

    struct Tree{
        std::vector<Node> nodes;
        void add_path_to_tree(const fs::path& file_path);
    } tree;
};


#endif
