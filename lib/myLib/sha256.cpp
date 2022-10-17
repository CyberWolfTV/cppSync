#include <string>
#include "first test.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <iostream>
#include <bitset>//dbg

namespace fs = std::experimental::filesystem;

//#include <cstring>


void SHA256::init(){
    wv[0] = h[0];
    wv[1] = h[1];
    wv[2] = h[2];
    wv[3] = h[3];
    wv[4] = h[4];
    wv[5] = h[5];
    wv[6] = h[6];
    wv[7] = h[7];
}


void SHA256::update(){
    std::cout << "upadet" << std::endl;
    // its filling all the w and doing the compression
    for(short i = 16; i <= 63; i++){
        w[i] = (
                w[i-16] + 
                (
                    ((w[i-15] >> 7) | (w[i-15] << 25)) |
                    ((w[i-15] >> 18) | (w[i-15] << 14)) |
                    // 10110110 >> 3 = 00010110
                    // 10110110 << 5 = 11000000
                    // 10110110 rot_r= 11010110
                    // xor both:       11010110 
                    (w[i-15] >> 3)
                ) + 
                w[i-7] +
                (   // used -15 everywhere here
                    ((w[i-2] >> 17) | (w[i-2] << 15)) |
                    ((w[i-2] >> 19) | (w[i-2] << 13)) |
                    (w[i-2] >> 10)
                )
            ) % 0x100000000;
    }
    
    // compression
    init(); //inits the wv[i]
    //abcdefgh
    unsigned int Temp1 = 0x00000000;
    unsigned int Temp2 = 0x00000000;
    for(int i = 0; i <= 63; i++){
        Temp1 = (wv[7] + (
            ((wv[4] >> 6) | (w[4] << 26))  |
            ((wv[4] >> 11) | (w[4] << 21)) |
            ((wv[4] >> 25) | (w[4] << 7))
            ) + (
            //(e and f) xor ((not e) and g)
            (wv[4] & wv[5]) | ((~wv[4]) & wv[6])
            ) + k[i] + w[i]) % 0x100000000;
        
        Temp2 = ((
            ((wv[0] >> 2) | (w[0] << 30))  |
            ((wv[0] >> 13) | (w[0] << 19)) |
            ((wv[0] >> 22) | (w[0] << 10))
            ) + (
            (wv[0] & wv[1]) | (wv[0] & wv[2]) | (wv[1] & wv[2])
            )) % 0x100000000; 
        

        wv[7] = wv[6];
        wv[6] = wv[5];
        wv[5] = wv[4];
        wv[4] = Temp1;
        wv[3] = wv[2];
        wv[2] = wv[1];
        wv[1] = wv[0];
        wv[0] = (Temp1 + Temp2) % 0x100000000;

        for(int i = 0; i <= 7; i++){
            h[i] += wv[i];
        }
        
    }
}




std::string SHA256::sha256(std::string filename){

    
    fs::path path = filename; 
    msg_len = fs::file_size(path);
    
    std::cout << msg_len/64 << std::endl;

    std::ifstream file(filename, std::ios::in | std::ios::binary);
    
    
    
    for(unsigned long long i = msg_len/64; i != 0; i--){
        // read 16 x 4 bytes into w[0] - w[15]
        //std::cout << "END" << std::endl;
        for (int i2 = 0; i2 <= 15; i2++){
            w[i2] &= 0x00000000;
            w[i2] |= (file.get() << 24);
            w[i2] |= (file.get() << 16);
            w[i2] |= (file.get() << 8);
            w[i2] |= file.get();
        }
        update();
    }
    //std::cout << "END" << std::endl;

    for (int i = 0; i <= 15; i++){
            w[i] = 0x00000000;
            if(!file.eof()){
                // ifstream.peek();
                if(file.eof()){std::cout << "wwfnhuwef";}
                char b = file.get();
                if(file.eof()){std::cout << "wwfnhuwef";}
                std::bitset<8> c(b);
                std::cout << c << '\n';
                std::cout << b << '\n';
                char a = file.get();
                std::cout << a << '\n';
                w[i] |= (file.get() << 24);
            } else{
                w[i] |= (0x80 << 24);
                std::cout << "1" << std::endl;
                break;
            }
            if(!file.eof()){
                w[i] |= (file.get() << 16);
            } else{
                std::bitset<32> x1(w[i]);
                std::cout << x1 << '\n';
                w[i] |= (0x80 << 24);
                
                std::cout << "2" << std::endl;
                std::bitset<32> x(w[i]);
                std::cout << x << '\n';
                break;
            }
            if(!file.eof()){
                w[i] |= (file.get() << 8);
            } else{
                w[i] |= (0x80 << 24);
                std::cout << "3" << std::endl;
                break;
            }
            if(!file.eof()){
                w[i] |= file.get();
            } else{
                w[i] |= (0x80 << 24);
                std::cout << "4" << std::endl;
                break;
            }
        }
    

    
    if(msg_len % 64 <= 447){
        //final stuff
        std::cout << "1.1" << std::endl;
        w[14] |= (msg_len >> 32);
        w[15] |= msg_len;
        update();
      //while(!file.eof()){}
    } else{
        std::cout << "2.2" << std::endl;
        update();

        for (int i = 0; i <= 15; i++){
            w[i] &= 0x00000000;
        }
        w[14] |= (msg_len >> 32);
        w[15] |= msg_len;
        // update, final stuff
    }

    


    //maybe write new
    /*/
    char buf[2*32+1];
    buf[2*32] = 0;
    for (int i = 0; i < 32; i++)
        sprintf(buf+i*2, "%02x", h[i]);
    return std::string(buf);*/
        //last chunk, needs to be <512-65 -> 1 + big endian int
        // otherwise add 0s and go for 1 more round;
        std::string abc;
    for (int i = 0; i < 8; i++)
        
        std::cout << std::hex << h[i];
    
    return "v";
}


/*
int main(){

    

    std::string msg = "hello world fdfrhderherhedhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh";

    

    return 1;
}*/