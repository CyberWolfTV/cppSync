#ifndef CPPSYNC_PATH_HPP
#define CPPSYNC_PATH_HPP

#include <string>
#include <filesystem>

namespace fs = std::filesystem;


class Path{
public:
    std::string path;

    std::string append(const std::string& path_to_append);
    fs::path to_fs_path();
};


#endif
