#include "aes.h"
#include "stdio.h"

char* aes_addkey(char* block, char* key){
    char* resultant = malloc(16);
    for(int i = 0; i < 16; i++){
        resultant[i] = block[i] ^ key[i];
    }

    return resultant;
}

char* aes_blockcrypt(unsigned char block[16], unsigned char key[16]){
    char* iv = aes_addkey(block, key);
    
    u_int8_t* subkeys = keyscheduler(key);

    for(int i = 0; i < 16; i++){
        printf("%i\n", (int)iv[i]);
    }

    for(int r = 1; r < 11; r++){
        
        uint32_t w[4];
        for(int i = 0; i < 4; i++){    
            w[i] = subbytes(bytemerge(iv[i * 4], iv[i * 4 + 1], iv[i * 4 + 2], iv[i * 4 + 3]));
            //ShiftRows
            w[i] = (w[i] << (i + 1) * 8) | (w[i] >> 32 - (i + 1) * 8);
            //Mix Cols
            uint8_t wordBytes[4];
            uint8_t transWordBytes[4];
            memcpy(wordBytes , &w[i], sizeof(uint32_t));
            transWordBytes[0] = 2 * wordBytes[0] + 3 * wordBytes[1] + wordBytes[2] + wordBytes[3];
            transWordBytes[1] = wordBytes[0] + 2 * wordBytes[1] + 3 * wordBytes[2] + wordBytes[3];
            transWordBytes[2] = wordBytes[0] + wordBytes[1] + 2 * wordBytes[2] + 3 * wordBytes[3];
            transWordBytes[3] = 3 * wordBytes[0] + wordBytes[1] + wordBytes[2] + 2 * wordBytes[3];
        }   

        
        iv = aes_addkey(w, (subkeys + 16 * r));   

    }
    //aes_rounds(iv, )
}




int main(){
    unsigned char block[16];
    unsigned char key[16];
    for (int i = 0; i < 16; i++){
        block[i] = 'h';
        key[i]= 'c';
    }
    aes_blockcrypt(block, key);
} 
