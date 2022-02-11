#include "keyscheduler.h"

#define ROUNDCONST {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36}

char* keyscheduler(unsigned char ikey[16]){
    unsigned char skey[176];

    for (int i = 0; i < 11; i++){
        int current_offset = i * 16;
    
        long w[4];
        long nw[4]; 
        
        for(int j = 0; j < 4; j++){
            int key_offset = current_offset + j * 4;
            w[j] = bytemerge(skey[key_offset], skey[key_offset + 1], skey[key_offset + 2], skey[key_offset + 3]);
        }

        nw[0] = w[0] ^ g(w[3]);
    }

}

long bytemerge(char b0, char b1, char b2, char b3){
    return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}  

long g(long w){
    return (w << 8) | (w >> 24);
    //http://www.linux-kongress.org/2009/slides/compiler_survey_felix_von_leitner.pdf
}
