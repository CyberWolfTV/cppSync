#ifndef CPPSYNC_LOCATION_HPP
#define CPPSYNC_LOCATION_HPP

#include <string>
#include <vector>
#include <map>

#include "../Tree/Node.hpp"
#include "../Configuration/Configs.hpp"


struct arguments{
    std::string name;
    bool compare = false;
    bool backup = false;
    bool find_duplicates = false;
    bool hash = false;
    bool configure = false;
    bool no_questions = false;
    bool compare_default = false;
};


class Location {
public:
    fs::path path;
    inline static std::string DATE_TIME;
    inline static struct arguments args;

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
        void add_path_to_tree(const fs::path& file_path, Configs* config);
    } tree;

    Configs configs;
    std::vector<Location> backup_locations;
};

#endif
