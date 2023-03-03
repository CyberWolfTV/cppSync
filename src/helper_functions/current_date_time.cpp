#include "helper_functions.hpp"


// https://stackoverflow.com/a/10467633/19808734
std::string current_date_time() {
    time_t now = time(0);
    struct tm time_struct{};
    char buf[80];
    time_struct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &time_struct);
    return buf;
}
