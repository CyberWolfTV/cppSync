#include <iostream>
#include <fstream>
#include "first test.hpp"

int main(){

    /*
    for(int i = 0; i<=4; i++){
        //std::cout << i;
    }
    // output: 01234

    std::ifstream file("test", std::ios::in | std::ios::binary);
    

    unsigned int w[2];
    for(unsigned long long i = 1; i != 0; i--){
        // read 16 x 4 bytes into w[0] - w[15]
        for (int i2 = 0; i2 <= 1; i2++){
            w[i2] &= 0x00000000;
            w[i2] |= (file.get() << 24);
            w[i2] |= (file.get() << 16);
            w[i2] |= (file.get() << 8);
            w[i2] |= file.get();
            std::cout << w[i2] << std::endl;
        }
    }
    */
   SHA256 test;
   std::cout << test.sha256("test") << std::endl;


   // test rotation:
   unsigned int i = 600000000;
   i = ((i >> 6) | (i << 26));
   std::cout << i;



   /*
   g++ first\ test.cpp playground.cpp -o ~/Clipboard/a.out
   alias build2="g++ first\ test.cpp playground.cpp -lstdc++fs -o ~/Clipboard/a.out"

   */

}