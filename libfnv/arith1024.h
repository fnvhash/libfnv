#ifndef __ARITH1024_H
#define __ARITH1024_H

#include <stdint.h>

void fnvInit1024from64(uint64_t x[16], uint64_t initialValue);
void fnvAdd1024(uint64_t x[16], uint64_t y[16]);
void fnvMul1024(uint64_t x[16], uint64_t y[16]);
void fnv1024xor8(uint64_t x[16], unsigned char c);

#endif
