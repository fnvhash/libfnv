#include "include/fnv/fnvtop.h"
#include "arith128.h"

void fnvInitArith128from64(struct Arith128 *kOut, uint64_t val) {
  kOut->d[0] = val;
  kOut->d[1] = 0;
}

void fnvArith128add(struct Arith128 *kOut, const struct Arith128 *kIn) {
  uint64_t oldSmall = kOut->d[0];
  kOut->d[0] += kIn->d[0];
  if (oldSmall > kOut->d[0]) {
    kOut->d[1] += 1;
  }
  kOut->d[1] += kIn->d[1];
}

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

void fnvArith128mul(struct Arith128 *kOut, const struct Arith128 *kIn) {
  uint64_t o[2], i[2];
  __uint128_t *bo = (__uint128_t *) &o[0];
  __uint128_t *bi = (__uint128_t *) &i[0];
  if (IS_BIG_ENDIAN) {
    o[1] = kOut->d[0];
    o[0] = kOut->d[1];
    i[1] = kIn->d[0];
    i[0] = kIn->d[1];
  } else {
    o[0] = kOut->d[0];
    o[1] = kOut->d[1];
    i[0] = kIn->d[0];
    i[1] = kIn->d[1];
  }
  *bo = (*bo) * (*bi);
  if (IS_BIG_ENDIAN) {
    kOut->d[0] = o[1];
    kOut->d[1] = o[0];
  } else {
    kOut->d[0] = o[0];
    kOut->d[1] = o[1];
  }
}

void fnvArith128xor8(struct Arith128 *kOut, unsigned char c) {
  kOut->d[0] ^= c;
}

void fnvArith128HexOut(char result[33], const struct Arith128 *kIn) {
  fnv64ResultHex(&result[ 0] , &kIn->d[1]);
  fnv64ResultHex(&result[16], &kIn->d[0]);
}

void fnvArith128DecIn(struct Arith128 *kOut, const char *str) {
  kOut->d[0] = 0;
  kOut->d[1] = 0;
  struct Arith128 ten;
  fnvInitArith128from64(&ten, 10);
  while (*str) {
    unsigned char c = *str;
    ++str;
    struct Arith128 cur;
    fnvInitArith128from64(&cur, c - '0');
    fnvArith128mul(kOut, &ten);
    fnvArith128add(kOut, &cur);
  }
}

