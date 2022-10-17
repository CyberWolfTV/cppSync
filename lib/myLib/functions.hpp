#pragma once
#include <string>

namespace my{
std::string currentDateTime();
std::string encode(std::string str);
std::string decode(std::string str);
int ask(std::string question);
std::string get_name(std::string tempname);
bool is_inited(std::string *name);
}
