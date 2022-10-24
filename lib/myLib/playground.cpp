#include <iostream>
#include <fstream>
#include "sha256.hpp"

int main(){
   
   std::cout << sha256("test") << std::endl;
}
/*
 *
 *   g++ first\ test.cpp playground.cpp -o ~/Clipboard/a.out
 *   alias build2="g++ sha256.cpp playground.cpp -lstdc++fs -o ~/Clipboard/a.out"
 *   alias build2="g++ sha256.cpp playground.cpp -lstdc++fs -o a.out"
 *
 */