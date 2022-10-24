#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include "../lib/myLib/sha256.hpp"

int main(){

    std::string command_string = "sha256sum -c hash";
    const char * command = command_string.c_str();

    

    std::ofstream touch_configfile(".config");
    touch_configfile.close();

    for(int i = 0; i <= 1000; i++){ 
        std::fstream config_file;
        config_file.open(".config",std::ios::out);
        
        for(int i2 = -i; i2 <= i; i2++){
            config_file << "A";
        }

        config_file.close();





        std::ofstream touch_hashfile("hash");
        touch_hashfile.close();

        std::fstream hash_file;
        hash_file.open("hash",std::ios::out);
        hash_file << sha256(".config") << "  .config" << std::endl;
        std::system(command);

        
    }
    return 0;

    //  alias build3="g++ Unit_test_sha256.cpp ../lib/myLib/sha256.cpp -lstdc++fs -o ~/Clipboard/a.out"

}