#include <string>
#include "sha256.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <iostream>
#include <iomanip>


#define DEBUG
//#define DEBUG_Padding
//#define DEBUG_fore___last_chunk
//#define DEBUG_w64
#define DEBUG_compression_algo
//#define DEBUG_h8
//#define DEBUG_last_byte

#ifdef DEBUG
#include <bitset>
#endif

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
    // its filling all the w
    std::cout << "w[64]:" << std::endl;
    for(short i = 16; i <= 63; i++){
        w[i] = (
                w[i-16] + 
                (
                    ((w[i-15] >> 7) | (w[i-15] << 25)) ^
                    ((w[i-15] >> 18) | (w[i-15] << 14)) ^
                    // 10110110 >> 3 = 00010110
                    // 10110110 << 5 = 11000000
                    // 10110110 rot_r= 11010110
                    // xor both:       11010110 
                    (w[i-15] >> 3)
                ) + 
                w[i-7] +
                (   // used -15 everywhere here
                    ((w[i-2] >> 17) | (w[i-2] << 15)) ^
                    ((w[i-2] >> 19) | (w[i-2] << 13)) ^
                    (w[i-2] >> 10)
                )
            ) % 0x100000000;

        #ifdef DEBUG_w64
        std::bitset<32> x(w[i]);
        std::cout << x << std::endl;
        #endif
    }
    
    // compression
    init(); //inits the wv[i]

    unsigned int Temp1 = 0x00000000;
    unsigned int Temp2 = 0x00000000;
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
        
        // abcdefgh
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




std::string SHA256::sha256(std::string filename){

    
    fs::path path = filename; 
    unsigned long long msg_len = fs::file_size(path);
    unsigned long long msg_len_counter = msg_len;
   
    #ifdef DEBUG
    std::cout << "msg_len / 64: " << msg_len/64 << std::endl;
    std::cout << "msg_len: " << msg_len << std::endl;
    std::cout << "msg_len +1 % 64: " << (msg_len + 1) % 64 << std::endl;
    #endif

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
    // add 0x0A = '\n' -> for having the filehash not
    // the hash of the content
    for (int i = 0; i <= 15; i++){
        if(msg_len_counter > 0){
            w[i] |= (file.get() << 24);
            msg_len_counter--;
                /*
                // ifstream.peek();
                if(file.eof()){std::cout << "where: ";}
                char b = file.get();
                if(file.eof()){std::cout << "here2: ";}
                std::bitset<8> c(b);
                std::cout << c << '\n';
                std::cout << b << '\n';
                char a = file.get();
                std::cout << a << '\n';
                //dbg end
                */
        } else{
            //w[i] |= (0x0A << 24);
            w[i] |= (0x80 << 24);

            #ifdef DEBUG_fore___last_chunk
            std::cout << "Exited in round " << i << std::endl;
            std::cout << "In step 1" << std::endl;
            std::bitset<32> x(w[i]);
            std::cout << x << std::endl;
            #endif

            break;
        }

        if(msg_len_counter > 0){
            w[i] |= (file.get() << 16);
            msg_len_counter--;
        } else{
            //w[i] |= (0x0A << 16);
            w[i] |= (0x80 << 16);

            #ifdef DEBUG_fore___last_chunk
            std::cout << "Exited in round " << i << std::endl;
            std::cout << "In step 2" << std::endl;
            std::bitset<32> x(w[i]);
            std::cout << x << std::endl;
            #endif

            break;
        }

        if(msg_len_counter > 0){
            w[i] |= (file.get() << 8);
            msg_len_counter--;
        } else{
            //w[i] |= (0x0A << 8);
            w[i] |= (0x80 << 8);

            #ifdef DEBUG_fore___last_chunk
            std::cout << "Exited in round " << i << std::endl;
            std::cout << "In step 3" << std::endl;
            std::bitset<32> x(w[i]);
            std::cout << x << std::endl;
            #endif

            break;
        }

        if(msg_len_counter > 0){
            w[i] |= file.get();
            msg_len_counter--;
        } else{
            //w[i] |= 0x0A;
            w[i] |= 0x80;
            
            #ifdef DEBUG_fore___last_chunk
            std::cout << "Exited in round " << i << std::endl;
            std::cout << "In step 4" << std::endl;
            std::bitset<32> x(w[i]);
            std::cout << x << std::endl;
            #endif

            break;
        }

        #ifdef DEBUG_fore___last_chunk
        std::cout << "End of the round " << i << std::endl;
        std::bitset<32> x(w[i]);
        std::cout << x << std::endl;
        #endif
    }

    #ifdef DEBUG_last_byte
    std::cout << "Last byte of tha file" << std::endl;
    std::bitset<8> x123(file.get());
    std::cout << x123 << std::endl;
    #endif
        
    

    // Add 0's and the msg_len
    if(msg_len % 64 <= 62){

        #ifdef DEBUG_Padding
        std::cout << "Way 1 (msg_len % 64 <= 447), 4 was added to msg_len" << std::endl;
        #endif
        w[14] |= (msg_len*8 >> 32);
        w[15] |= msg_len*8;

        #ifdef DEBUG_Padding
        std::cout << "Last chunk, (way 1)" << std::endl << "The 64bit endian thing...:" << std::endl;
        std::bitset<64> xmsg(msg_len*8);
        std::cout << xmsg << std::endl;
        std::bitset<32> x2(w[14]);
        std::cout << x2;
        std::bitset<32> x11(w[15]);
        std::cout << x11 << std::endl;
        #endif

        update();
    } else{
        
        #ifdef DEBUG_Padding
        std::cout << "way 2 (msg_len % 64 > 447), 4 was added to msg_len" << std::endl;
        #endif

        update();

        for (int i = 0; i <= 15; i++){
            w[i] &= 0x00000000;
        }
        w[14] |= (msg_len*8 >> 32);
        w[15] |= msg_len*8;

        #ifdef DEBUG_Padding
        std::cout << "Last chunk, (way 1)" << std::endl << "The 64bit endian thing...:" << std::endl;
        std::bitset<64> xmsg(msg_len*8);
        std::cout << xmsg << std::endl;
        std::bitset<32> x2(w[14]);
        std::cout << x2;
        std::bitset<32> x11(w[15]);
        std::cout << x11 << std::endl;
        #endif

        update();
    }

    #ifdef DEBUG_h8
    // values are incorrect rn (19.10.22)
    std::bitset<32> h1(h[0]);
        std::cout << h1 << std::endl;
    std::bitset<32> h2(h[1]);
        std::cout << h2 << std::endl;
    std::bitset<32> h3(h[2]);
        std::cout << h3 << std::endl;
    std::bitset<32> h4(h[3]);
        std::cout << h4 << std::endl;
    std::bitset<32> h5(h[4]);
        std::cout << h5 << std::endl;
    std::bitset<32> h6(h[5]);
        std::cout << h6 << std::endl;
    std::bitset<32> h7(h[6]);
        std::cout << h7 << std::endl;
    std::bitset<32> h8(h[7]);
        std::cout << h8 << std::endl;
    #endif
    
    // Return the Hash
    std::stringstream hash;
    for (int i = 0; i < 8; i++){
        hash << std::setfill('0') << std::setw(8) << std::hex << h[i];
    }

    std::cout << "\n\nHash:\n";

    return hash.str();
}

std::string sha256(std::string filename){
    SHA256 hashfunction;
    return hashfunction.sha256(filename);
}