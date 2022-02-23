#include "aes.h"
#include "stdio.h"
#include "math/GF28.h"

uint8_t* aes_addkey(uint8_t* block, uint8_t* key){
    for(int i = 0; i < 16; i++){
        //printf("Addkey %x\n", block[i] ^ key[i]);
        block[i] = block[i] ^ key[i];
        //printf("\n Round %i: Block %x, Key %x, Result %x", i, block[i], key[i], resultant[i]);
    }

    return block;
}

uint8_t* aes_blockcrypt(uint8_t block[16], uint8_t* subkeys){
    uint8_t* iv = malloc(16);
    iv = aes_addkey(block, subkeys);

    for(int r = 1; r < 11; r++){ 
        uint32_t w[4];

        /*printf("\nBlock pre operations\n");
        for(int i = 0; i < 4; i++){
            printf("%x ", bytemerge(iv[i * 4], iv[i * 4 + 1], iv[i * 4 + 2], iv[i * 4 + 3]));
        }*/

        for(int i = 0; i < 4; i++){    
            w[i] = subbytes(bytemerge(iv[i], iv[i + 4], iv[i + 8], iv[i + 12]));

            //ShiftRows
            w[i] = (w[i] << (i * 8)) | (w[i] >> (32 - i * 8));
            printf("Shift rows %i: %x ", i, w[i]);
        }   

        uint8_t* postBytes = (uint8_t*)w;
        uint8_t transPostBytes[16];
        //memcpy(postBytes, w, sizeof(uint32_t) * 4);
        /*printf("post %x%x%x%x\n", postBytes[3], postBytes[2], postBytes[1], postBytes[0]);
        printf("word 0 %x\n", w[0]);
        printf("post %x%x%x%x\n", postBytes[7], postBytes[6], postBytes[5], postBytes[4]);
        printf("word 1 %x\n", w[1]);

        printf("Check %x%x%x%x\n", postBytes[3], postBytes[7], postBytes[11], postBytes[15]); //w 0
        printf("Check %x%x%x%x\n", postBytes[2], postBytes[6], postBytes[10], postBytes[14]); //w 1
        printf("Check %x%x%x%x\n", postBytes[1], postBytes[5], postBytes[9], postBytes[13]); //w 2
        printf("Check %x%x%x%x\n", postBytes[0], postBytes[4], postBytes[8], postBytes[12]); //w 3  
        */      
        //Mix Cols
        for(int i = 0; i < 4; i++){
            int r = i * 4;
            transPostBytes[r] = gf2_8mult(postBytes[3 - i], 2) ^ gf2_8mult(postBytes[7 - i], 3) ^ postBytes[11 - i] ^ postBytes[15 - i];
            transPostBytes[r + 1] = postBytes[3 - i] ^ gf2_8mult(postBytes[7 - i], 2) ^ gf2_8mult(postBytes[11 - i], 3) ^ postBytes[15 - i];
            transPostBytes[r + 2] = postBytes[3 - i] ^ postBytes[7 - i] ^ gf2_8mult(postBytes[11 - i], 2) ^ gf2_8mult(postBytes[15 - i], 3);
            transPostBytes[r + 3] = gf2_8mult(postBytes[3 - i], 3) ^ postBytes[7 - i] ^ postBytes[11 - i] ^ gf2_8mult(postBytes[15 - i], 2);

           
        }

        printf("Mix Ouput\n ");
        for(int i = 0; i < 16; i++){
            printf("%x", transPostBytes[i]);
            if((i + 1) % 4 == 0 && i != 0){
                printf(" ");
            }
        }
        
        memcpy(w, transPostBytes, sizeof(uint32_t) * 4);

        printf("\nKey Used\n ");
        uint8_t *key = subkeys + 16 * r;
        for(int i = 0; i < 16; i++){
            printf("%x", key[i]);
            if((i+1) % 4 == 0 && i != 0){
                printf(" ");
            }

        }

        printf("\nRound Prekey\n ");
        for(int i = 0; i < 4; i++){
            printf("%x ", w[i]);
        }

        memcpy(iv, aes_addkey(w, (subkeys + 16 * r)), sizeof(w));   

        printf("\nRound results:\n ");
        for(int i = 0; i < 16; i++){
            printf("%x", iv[i]);
            if((i+1) % 4 == 0 && i != 0){
                printf(" ");
            }
        }
        printf("\n\n\n\n");

    }
    printf("Final Result\n");
    for(int i = 0; i < 16; i++){
        printf("%x ", iv[i]);
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

    u_int8_t* subkeys = keyscheduler(key);
    uint8_t* result = aes_blockcrypt(block, subkeys);

    printf("\n I am the result \n");
    for(int i = 0; i < 16; i++){
        printf("%x\n", result[i]);
    }

    printf("\n%x\n", gf2_8mult(0b10010110, 0b101));
} 
