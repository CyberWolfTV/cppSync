#include "Location.hpp"

my::Location::Location(std::string arg_name,
                       std::string arg_datetime,
                       std::map<std::string, bool> arg_options
                       ){
    datetime = arg_datetime;
    name = arg_name;
    options = arg_options;

    loadconfig();
}