#ifndef CPPSYNC_LOCATION_HPP
#define CPPSYNC_LOCATION_HPP

#include <string>
#include <vector>
#include <map>


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
    std::string path;
    inline static std::string DATE_TIME;
    inline static struct arguments args;

    explicit Location(std::string arg_path);

    void init() const;

    void load_configs(bool is_main_location);
    struct configurations{
        void configure(std::string loc_path);
        void save_configs();
        static std::vector<std::string> parse_list_file(const std::string& file_path);
        int old_versions;
        std::vector<Location> backup_locations;
        std::vector<std::string> whitelist;
        std::vector<std::string> blacklist;
    } configs;

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

    void restore();
};

#endif
