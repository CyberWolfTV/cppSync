#include "Location/Location.hpp"
#include "helper_functions/helper_functions.hpp"

#include <filesystem>

namespace fs = std::filesystem;


int main(int argc, char *argv[]) {
    parse_args(argc, argv, &Location::args);

    Location::args.name = fs::current_path().string() + "/" + Location::args.name;
    fs::current_path(Location::args.name);

    Location::DATE_TIME = current_date_time();
    Location main_instance(Location::args.name);
    main_instance.load_configs(true);


    if(Location::args.configure){
        main_instance.configs.configure(main_instance.path);
    }

    if(Location::args.hash || Location::args.backup){
        main_instance.get_hashes();
    }

    if(Location::args.find_duplicates){
        main_instance.get_hashes();
        main_instance.find_duplicates();
    }

    if(Location::args.compare_default){
        // not implemented yet
    }

    if(Location::args.compare){
        user_compare(main_instance);
    }

    if(Location::args.backup){
        main_instance.backup();
    }

    return 0;
}
