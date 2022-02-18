#include "keyscheduler.h"

uint8_t* aes_blockcrypt(uint8_t block[16] , uint8_t key[16]);
uint8_t* aes_addkey(uint8_t* block, uint8_t* key);