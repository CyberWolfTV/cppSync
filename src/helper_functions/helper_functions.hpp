#ifndef CPPSYNC_HELPER_FUNCTIONS_HPP
#define CPPSYNC_HELPER_FUNCTIONS_HPP


#include <string>
#include <map>
#include <vector>

#include "../Location/Location.hpp"


// cppSync_help.cpp
void cppSync_help();


// current_date_time.cpp
// https://stackoverflow.com/a/10467633/19808734
std::string current_date_time();


// parse_args.cpp
void parse_args(int argc, char *argv[], struct arguments * args);


// raw_inputs.cpp
bool ask(const std::string& question, char default_answer);
int get_int(const std::string& question);


// json.cpp
std::map<std::string, std::string> json_to_map(std::string json);
class json {
private:
    std::string json_object;
public:
    void addpair(const std::string& key, const std::string& value);
    std::string get();
};


// get_name.cpp
std::string get_name(std::string name);


// get_state.cpp
std::map<std::string, std::string> get_state(const std::string& path);


// escaping.cpp
std::string encode(std::string const *str);
std::string decode(std::string str);


// user_compare.cpp
void user_compare(Location main_instance);
void print_compared(struct Location::comp_changes *changes);


// get_choice.cpp
std::string get_choice(std::string const *path);


#endif
