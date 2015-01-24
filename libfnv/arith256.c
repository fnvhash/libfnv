#include <string.h>
#include "arith256.h"
#include "mgmp.h"

void fnvInit256from64(uint64_t x[4], uint64_t initialValue) {
  memset(&x[1], 0, 24);
  x[0] = initialValue;
}

struct u256b
{
  uint64_t lo;
  uint64_t mid;
  __uint128_t hi;
};

void fnvAdd256(uint64_t px[4], uint64_t py[4]) {
  struct u256b *x= (struct u256b *) &px[0];
  struct u256b *y= (struct u256b *) &py[0];

  __uint128_t lo = (__uint128_t) x->lo + y->lo;
  __uint128_t mid = (__uint128_t) x->mid + y->mid + (lo >> 64);
    x->hi = x->hi + y->hi + (mid >> 64);
    x->lo = lo;
    x->mid = mid;
}

void fnvMul256(uint64_t px[4], uint64_t py[4]) {
  struct u256b *x= (struct u256b *) &px[0];
  struct u256b *y= (struct u256b *) &py[0];
  __uint128_t t1 = (__uint128_t) x->lo * y->lo;
  __uint128_t t2 = (__uint128_t) x->lo * y->mid;
  __uint128_t t3 = x->lo * y->hi;
  __uint128_t t4 = (__uint128_t) x->mid * y->lo;
  __uint128_t t5 = (__uint128_t) x->mid * y->mid;
  uint64_t t6 = x->mid * y->hi;
  __uint128_t t7 = x->hi * y->lo;
  uint64_t t8 = x->hi * y->mid;

  uint64_t lo = t1;
  __uint128_t m1 = (t1 >> 64) + (uint64_t)t2;
  uint64_t m2 = m1;
  __uint128_t mid = (__uint128_t) m2 + (uint64_t)t4;
  __uint128_t hi = (t2 >> 64) + t3 + (t4 >> 64) + t5 + ((__uint128_t) t6 << 64) + t7
     + ((__uint128_t) t8 << 64) + (m1 >> 64) + (mid >> 64);
  x->lo = lo;
  x->mid = mid;
  x->hi = hi;
}

void fnv256xor8(uint64_t x[4], unsigned char c) {
  x[0] ^= c;
}

