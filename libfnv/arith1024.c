#include <string.h>
#include "../libfnv/include/fnv/fnvtop.h"
#include "arith1024.h"
#include "mgmp.h"

void fnvInit1024from64(uint64_t x[16], uint64_t initialValue) {
  memset(&x[1], 0, 128-8);
  x[0] = initialValue;
}

void fnvAdd1024(uint64_t px[16], uint64_t py[16]) {
  uint64_t c=0;
  int i;
  for (i = 0; i < 16; ++i) {
    __uint128_t sum = (__uint128_t) px[i] + (__uint128_t) py[i] + (__uint128_t) c;
    c = (sum >> 64);
    px[i] = sum & ((((__uint128_t) 1) << 64) - ((__uint128_t)1));
  }
}

void fnvMul1024(uint64_t px[16], uint64_t py[16]) {
  uint64_t presult[33];
  fnv_mpn_mul((uint64_t *) presult, (const uint64_t *) px, 16, (const uint64_t *) py, 16);
  memcpy(px, presult, 128);
}

void fnv1024xor8(uint64_t x[16], unsigned char c) {
  x[0] ^= c;
}
