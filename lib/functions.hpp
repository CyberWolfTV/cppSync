#pragma once

#include <string>

namespace my{
    std::string currentDateTime(); // returns datetime

    std::string encode(std::string str);
    std::string decode(std::string str);
    // kinda url-en-/decoding for json

    bool ask(std::string question);
    // question? [y/n] -> returns true / false

    std::string get_name(std::string tempname);
    bool is_inited();

    void help();
    // prints help text and exits
}
