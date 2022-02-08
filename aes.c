#include "aes.h"
#include "stdio.h"

char* aes_addkey(unsigned char block[16], unsigned char key[16]){
    char* resultant[16];
    for(int i = 0; i < 16; i++){
        resultant[i] = block[i] ^ key[i];
    }

    return resultant;
}

char* aes_blockcrypt(unsigned char block[16], unsigned char key[16]){
    unsigned char* iv = aes_addkey(block, key);
    
    for(int i = 0; i < 16; i++){
        printf("%i\n", (int)iv[i]);
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
