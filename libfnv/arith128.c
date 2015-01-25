#include "include/fnv/fnvtop.h"
#include "arith128.h"
#include "mgmp.h"
#include "ifnv.h"

void fnvInitArith128from64(struct Arith128 *kOut, uint64_t val) {
  kOut->d[0] = val;
  kOut->d[1] = 0;
}

void fnvArith128add(struct Arith128 *kOut, const struct Arith128 *kIn) {
  *((__uint128_t *) kOut) += *((__uint128_t *) kIn);
}

void fnvArith128mul(struct Arith128 *kOut, const struct Arith128 *kIn) {
  *((__uint128_t *) kOut) *= *((__uint128_t *) kIn);
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

