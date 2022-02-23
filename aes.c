#include "aes.h"
#include "stdio.h"
#include "math/GF28.h"

uint8_t* aes_addkey(uint8_t* block, uint8_t* key){
    for(int i = 0; i < 16; i++){
        block[i] = block[i] ^ key[i];
    }

    return block;
}

uint8_t* aes_blockcrypt(uint8_t block[16], uint8_t* subkeys){
    uint8_t* iv = malloc(16);
    iv = aes_addkey(block, subkeys);

    for(int r = 1; r < 11; r++){ 
        uint32_t w[4];

        for(int i = 0; i < 4; i++){    
            w[i] = subbytes(bytemerge(iv[i], iv[i + 4], iv[i + 8], iv[i + 12]));

            //ShiftRows
            w[i] = (w[i] << (i * 8)) | (w[i] >> (32 - i * 8));
        }   

        uint8_t* postBytes = (uint8_t*)w;
        uint8_t transPostBytes[16];

        //Mix Cols
        if(r != 10){
            for(int i = 0; i < 4; i++){
                int r = i * 4;
                transPostBytes[r] = gf2_8mult(postBytes[3 - i], 2) ^ gf2_8mult(postBytes[7 - i], 3) ^ postBytes[11 - i] ^ postBytes[15 - i];
                transPostBytes[r + 1] = postBytes[3 - i] ^ gf2_8mult(postBytes[7 - i], 2) ^ gf2_8mult(postBytes[11 - i], 3) ^ postBytes[15 - i];
                transPostBytes[r + 2] = postBytes[3 - i] ^ postBytes[7 - i] ^ gf2_8mult(postBytes[11 - i], 2) ^ gf2_8mult(postBytes[15 - i], 3);
                transPostBytes[r + 3] = gf2_8mult(postBytes[3 - i], 3) ^ postBytes[7 - i] ^ postBytes[11 - i] ^ gf2_8mult(postBytes[15 - i], 2);

            
            }
        } else {
            for(int i = 0; i < 4; i++){
                int r = i * 4;
                transPostBytes[r] = postBytes[3 - i];
                transPostBytes[r + 1] = postBytes[7 - i];
                transPostBytes[r + 2] = postBytes[11 - i];
                transPostBytes[r + 3] = postBytes[15 - i];
            }
        }

        memcpy(w, transPostBytes, sizeof(uint32_t) * 4);

        memcpy(iv, aes_addkey(w, (subkeys + 16 * r)), sizeof(w));   
    }

    return iv;
}

int main(){

    uint8_t block[16];
    uint8_t key[16];

    for (int i = 0; i < 16; i++){
        block[i] = 0x11;
        key[i]= 0x22;
    }

    printf("\nKey Used:\n");
    for(int i = 0; i < 16; i++){
        printf("%x ", key[i]);
    }
     printf("\nBlock Used: (HEX)\n");
    for(int i = 0; i < 16; i++){
        printf("%x ", block[i]);
    }

    u_int8_t* subkeys = keyscheduler(key);
    uint8_t* result = aes_blockcrypt(block, subkeys);
    

    printf("\nResult: \n");
    for(int i = 0; i < 16; i++){
        printf("%02x ", result[i]);
    }
    printf("\n\n");
} 
