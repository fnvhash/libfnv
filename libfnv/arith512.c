#include <string.h>
#include "../libfnv/include/fnv/fnvtop.h"
#include "arith512.h"
#include "mgmp.h"

void fnvInit512from64(uint64_t x[8], uint64_t initialValue) {
  memset(&x[1], 0, 64-8);
  x[0] = initialValue;
}

void fnvAdd512(uint64_t px[8], uint64_t py[8]) {
  uint64_t c=0;
  int i;
  for (i = 0; i < 8; ++i) {
    __uint128_t sum = (__uint128_t) px[i] + (__uint128_t) py[i] + (__uint128_t) c;
    c = (sum >> 64);
    px[i] = sum & ((((__uint128_t) 1) << 64) - ((__uint128_t)1));
  }
}

void fnvMul512(uint64_t px[8], uint64_t py[8]) {
  uint64_t presult[17];
  fnv_mpn_mul((uint64_t *) presult, (const uint64_t *) px, 8, (const uint64_t *) py, 8);
  memcpy(px, presult, 64);
}

void fnv512xor8(uint64_t x[8], unsigned char c) {
  x[0] ^= c;
}

