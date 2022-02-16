#include "keyscheduler.h"

char* aes_blockcrypt(unsigned char block[16] , unsigned char key[16]);
char* aes_addkey(char* block, char* key);