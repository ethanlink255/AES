#include "GF28.h"
#include "stdio.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) //https://stackoverflow.com/questions/523724/c-c-check-if-one-bit-is-set-in-i-e-int-variable
//TODO: Research Macros


//TODO: Very Very inefficient
uint8_t gf2_8mult(uint8_t m1, uint8_t m2){
    uint8_t result = 0; 
    uint8_t calcs[8];

    uint8_t running = m1;
    calcs[0] = m1;
    for(int i = 1; i < 8; i++){
        running = fxx(running);
        calcs[i] = running;
    }

    for(int i = 7; i >= 0; i--){
        if(CHECK_BIT(m2, i)){
            result ^= calcs[i];
        }
    }
    return result;
}

uint8_t fxx(uint8_t fx){
    if (fx >= 0b10000000){
        return (fx << 1) ^ 0b00011011;
    } else {
        return (fx << 1);
    }
}