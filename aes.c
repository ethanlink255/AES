#include "aes.h"
#include "stdio.h"

uint8_t* aes_addkey(uint8_t* block, uint8_t* key){
    uint8_t* resultant = malloc(16);
    for(int i = 0; i < 16; i++){
        resultant[i] = block[i] ^ key[i];
        printf("\n Round %i: Block %x, Key %x, Result %x", i, block[i], key[i], resultant[i]);
    }

    return resultant;
}

uint8_t* aes_blockcrypt(uint8_t block[16], uint8_t* subkeys){
    uint8_t* iv = malloc(16);
    printf("First Block:\n");

    for(int i = 0; i < 16; i++){
        printf("%x ", block[i]);
    }

    iv = aes_addkey(block, subkeys);

    printf("\nBlock post addkey:\n");
    for(int i = 0; i < 16; i++){
        printf("%x ", iv[i]);
    }
    
    for(int r = 1; r < 11; r++){ 
        uint32_t w[4];
        for(int i = 0; i < 4; i++){    
            w[i] = subbytes(bytemerge(iv[i * 4], iv[i * 4 + 1], iv[i * 4 + 2], iv[i * 4 + 3]));
           
            printf("\nBlock post SubBytes Round %i:\n", i);
            for(int i = 0; i < 4; i++){
                printf("%x ", w[i]);
            }
            //ShiftRows
            w[i] = (w[i] << (i * 8)) | (w[i] >> (32 - i * 8));
            printf("\nBlock post Shift Rows Round %i:\n", i);
            for(int i = 0; i < 4; i++){
                printf("%x ", w[i]);
            }
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

    for(int i = 0; i < 16; i++){
        printf("%x\n", result[i]);
    }
} 
