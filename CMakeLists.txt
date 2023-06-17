cmake_minimum_required(VERSION 3.24)
project(cppSync)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lstdc++fs -std=c++17")

add_executable(cppSync
        src/main.cpp
        src/helper_functions/parse_args.cpp
        src/helper_functions/cppSync_help.cpp
        src/helper_functions/get_name.cpp
        src/helper_functions/current_date_time.cpp
        src/Location/Location.cpp
        src/helper_functions/raw_inputs.cpp
        src/hash_functions/sha256.cpp
        src/Location/methods/init.cpp
        src/helper_functions/user_compare.cpp
        src/helper_functions/get_choice.cpp
        src/Location/methods/load_configs.cpp
        src/helper_functions/json.cpp
        src/helper_functions/escaping.cpp
        src/helper_functions/get_state.cpp
        src/Location/methods/backup.cpp
        src/Location/methods/restore.cpp
        src/Location/methods/hashing.cpp
        src/Location/methods/compare.cpp
        src/Location/methods/find_duplicates.cpp
        src/Location/methods/is_in_scope.cpp
        src/Tree/Node.cpp
        src/Configuration/methods/load_node_configs.cpp
        src/Configuration/methods/load_location_config.cpp
        src/Tree/methods/get_node_config_ptr.cpp
        src/Location/methods/add_path_to_tree.cpp
        src/Configuration/methods/get_clean_lines.cpp
        src/Tree/methods/detect_git_repos.cpp
        src/Tree/methods/get_leafs.cpp)
