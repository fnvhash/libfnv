#ifndef __ARITH512_H
#define __ARITH512_H

#include <stdint.h>

void fnvInit512from64(uint64_t x[8], uint64_t initialValue);
void fnvAdd512(uint64_t x[8], uint64_t y[8]);
void fnvMul512(uint64_t x[8], uint64_t y[8]);
void fnv512xor8(uint64_t x[8], unsigned char c);

#endif
