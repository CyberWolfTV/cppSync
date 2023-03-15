#include "../Location.hpp"


bool Location::is_in_scope(std::string file_or_dir){
    // TODO: write this function
    // always exclude .cppSync

    //  std::size_t found = str.find_last_of("/\\");
    //  std::cout << " path: " << str.substr(0,found) << '\n';
    //  std::cout << " file: " << str.substr(found+1) << '\n';

    //  path: /usr/bin
    //  file: man

    //  path: c:\windows
    //  file: winhelp.exe
    return true;
}
