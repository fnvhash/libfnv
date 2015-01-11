#include <string.h>
#include "../libfnv/include/fnv/fnvtop.h"
#include "arith1024.h"

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
  int i;
  uint64_t acc[16], dub[16], tdub[16];
  memset(acc, 0, 128);
  memcpy(dub, py, 128);
  for (i = 0; i < 1024; ++i) {
    uint64_t *p = px+(i >> 6);
    uint64_t m = i & 63;
    m = 1ULL << m;
    if ((*p) & m) {
      fnvAdd1024(acc, dub);
    }
    memcpy(tdub, dub, 128);
    int j;
    for (j = 0; j < 16; ++j) {
      dub[j] = tdub[j] << 1;
    }
    for (j = 1; j < 16; ++j) {
      dub[j] |= (tdub[j-1] >> 63);
    }
  }
  memcpy(px, acc, 128);
}

void fnv1024xor8(uint64_t x[16], unsigned char c) {
  x[0] ^= c;
}
