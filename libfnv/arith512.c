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
#if 1
  uint64_t presult[17];
  fnv_mpn_mul((uint64_t *) presult, (const uint64_t *) px, 8, (const uint64_t *) py, 8);
  memcpy(px, presult, 64);
#else
  int i;
  uint64_t acc[8], dub[8], tdub[8];
  memset(acc, 0, 64);
  memcpy(dub, py, 64);
  for (i = 0; i < 512; ++i) {
    uint64_t *p = px+(i >> 6);
    uint64_t m = i & 63;
    m = 1ULL << m;
    if ((*p) & m) {
      fnvAdd512(acc, dub);
    }
    memcpy(tdub, dub, 64);
    int j;
    for (j = 0; j < 8; ++j) {
      dub[j] = tdub[j] << 1;
    }
    for (j = 1; j < 8; ++j) {
      dub[j] |= (tdub[j-1] >> 63);
    }
  }
  memcpy(px, acc, 64);
#endif
}

void fnv512xor8(uint64_t x[8], unsigned char c) {
  x[0] ^= c;
}

