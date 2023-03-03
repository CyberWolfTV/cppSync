#include "sha256.hpp"

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <iomanip>

namespace fs = std::filesystem;


std::string sha256(const std::string& filename){
    sha256_class hash_function;
    return hash_function.sha256(filename);
}

void sha256_class::init(){
    wv[0] = h[0];
    wv[1] = h[1];
    wv[2] = h[2];
    wv[3] = h[3];
    wv[4] = h[4];
    wv[5] = h[5];
    wv[6] = h[6];
    wv[7] = h[7];
}


void sha256_class::update(){
    // its filling all the w
    for(short i = 16; i <= 63; i++){
        w[i] = (
                       w[i-16] +
                       (
                               ((w[i-15] >> 7) | (w[i-15] << 25)) ^
                               ((w[i-15] >> 18) | (w[i-15] << 14)) ^
                               (w[i-15] >> 3)
                       ) +
                       w[i-7] +
                       (
                               ((w[i-2] >> 17) | (w[i-2] << 15)) ^
                               ((w[i-2] >> 19) | (w[i-2] << 13)) ^
                               (w[i-2] >> 10)
                       )
               ) % 0x100000000;
    }

    // compression
    init(); //inits the wv[i]

    unsigned int Temp1;
    unsigned int Temp2;
    for(int i = 0; i <= 63; i++){
        Temp1 = (wv[7] + (
                ((wv[4] >> 6) | (wv[4] << 26))  ^
                ((wv[4] >> 11) | (wv[4] << 21)) ^
                ((wv[4] >> 25) | (wv[4] << 7))
        ) + (
                         //(e and f) xor ((not e) and g)
                         (wv[4] & wv[5]) | ((~wv[4]) & wv[6])
                 ) + k[i] + w[i]) % 0x100000000;

        Temp2 = (
                        (((wv[0] >> 2) | (wv[0] << 30))  ^
                         ((wv[0] >> 13) | (wv[0] << 19)) ^
                         ((wv[0] >> 22) | (wv[0] << 10)))
                        + ((wv[0] & wv[1]) ^ (wv[0] & wv[2]) ^ (wv[1] & wv[2]))
                ) % 0x100000000;

        wv[7] = wv[6];
        wv[6] = wv[5];
        wv[5] = wv[4];
        wv[4] = (wv[3] + Temp1) % 0x100000000;
        wv[3] = wv[2];
        wv[2] = wv[1];
        wv[1] = wv[0];
        wv[0] = (Temp1 + Temp2) % 0x100000000;
    }

    for(int i = 0; i <= 7; i++){
        h[i] = (wv[i] + h[i])  % 0x100000000;
    }
}




std::string sha256_class::sha256(const std::string& filename){
    fs::path path = filename;
    unsigned long long msg_len = fs::file_size(path);
    unsigned long long msg_len_counter = msg_len;

    std::ifstream file(filename, std::ios::in | std::ios::binary);

    for(unsigned long long i = msg_len/64; i != 0; i--){
        // read 16 x 4 bytes into w[0] - w[15]
        // update() after every round
        for (int i2 = 0; i2 <= 15; i2++){
            w[i2] &= 0x00000000;
            w[i2] |= (file.get() << 24);
            w[i2] |= (file.get() << 16);
            w[i2] |= (file.get() << 8);
            w[i2] |= file.get();
            msg_len_counter -= 4;
        }
        update();
    }

    //reset w[i]
    for(int i = 0; i<=15; i++){
        w[i] = 0x00000000;
    }

    // Read the rest of the file and write it to the w[]
    // add 0x0A = '\n' -> for having the files hash not
    // the hash of the content
    for (int i = 0; i <= 15; i++){
        if(msg_len_counter > 0){
            w[i] |= (file.get() << 24);
            msg_len_counter--;
        } else{
            w[i] |= (0x80 << 24);
            break;
        }

        if(msg_len_counter > 0){
            w[i] |= (file.get() << 16);
            msg_len_counter--;
        } else{
            w[i] |= (0x80 << 16);
            break;
        }

        if(msg_len_counter > 0){
            w[i] |= (file.get() << 8);
            msg_len_counter--;
        } else{
            w[i] |= (0x80 << 8);
            break;
        }

        if(msg_len_counter > 0){
            w[i] |= file.get();
            msg_len_counter--;
        } else{
            w[i] |= 0x80;
            break;
        }
    }

    // Add 0's and the msg_len
    if(msg_len % 64 <= 56){
        w[14] |= (msg_len*8 >> 32);
        w[15] |= msg_len*8;

        update();
    } else{
        update();

        for (int i = 0; i <= 15; i++){
            w[i] &= 0x00000000;
        }
        w[14] |= (msg_len*8 >> 32);
        w[15] |= msg_len*8;
        update();
    }

    // Return the Hash
    std::stringstream hash;
    for(unsigned int i : h){
        hash << std::setfill('0') << std::setw(8) << std::hex << i;
    }

    // Reset the variables...
    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5] = 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;
    for (int i = 0; i <= 15; i++){
        w[i] &= 0x00000000;
    }
    for(int i = 0; i <= 7; i++){
        wv[i] = 0;
    }
    return hash.str();
}
