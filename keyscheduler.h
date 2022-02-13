#include "stdio.h"
#include "stdint.h"
#include <string.h>
#include <stdlib.h>

uint8_t* keyscheduler(uint8_t ikey[16]);
uint32_t bytemerge(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);
uint32_t g(uint32_t w, uint8_t rc);
uint32_t subbytes(uint32_t w);