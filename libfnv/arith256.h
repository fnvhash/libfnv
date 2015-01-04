#ifndef __ARITH256_H
#define __ARITH256_H

#include <stdint.h>

void fnvInit256from64(uint64_t x[4], uint64_t initialValue);
void fnvAdd256(uint64_t x[4], uint64_t y[4]);
void fnvMul256(uint64_t x[4], uint64_t y[4]);
void fnv256xor8(uint64_t x[4], unsigned char c);

#endif
