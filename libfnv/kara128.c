#include "include/fnv/fnvtop.h"
#include "kara128.h"

void fnvInitKara128from64(struct Kara128 *kOut, uint64_t val) {
  kOut->d[0] = val;
  kOut->d[1] = 0;
}

void fnvKara128add(struct Kara128 *kOut, const struct Kara128 *kIn) {
  uint64_t oldSmall = kOut->d[0];
  kOut->d[0] += kIn->d[0];
  if (oldSmall > kOut->d[0]) {
    kOut->d[1] += 1;
  }
  kOut->d[1] += kIn->d[1];
}

#define BASEPOWTWO 16
#define BASEPLACES 8

#define ANDMASK ((1 << BASEPOWTWO) - 1)

void fnvKara128mul(struct Kara128 *kOut, const struct Kara128 *kIn) {
  uint64_t acc[2*BASEPLACES];
  uint32_t out[BASEPLACES], in[BASEPLACES];
  int i, j;
  memset(acc, 0, sizeof(acc));
  for (i = 0; i < BASEPLACES; ++i) {
    out[i] = kOut->d[i/4] >> BASEPOWTWO*(i%4);
    out[i] &= ANDMASK;
    in[i] = kIn->d[i/4] >> BASEPOWTWO*(i%4);
    in[i] &= ANDMASK;
  }
  for (i = 0; i < BASEPLACES; ++i) {
    for (j = 0; j < BASEPLACES; ++j) {
      int s = i + j;
      acc[s] += ((uint32_t) (out[i] * in[j]));
    }
  }
  uint64_t carry = 0;
  for (i = 0; i < 2 * BASEPLACES; ++i) {
    acc[i] += carry;
    carry = acc[i];
    carry >>= BASEPOWTWO;
    acc[i] &= ANDMASK;
  }
  for (i = BASEPLACES-1; i >= 0; --i) {
    kOut->d[i/4] <<= BASEPOWTWO;
    kOut->d[i/4] |= acc[i];
  }
}

void fnvKara128xor8(struct Kara128 *kOut, unsigned char c) {
  kOut->d[0] ^= c;
}

void fnvKara128HexOut(char result[33], const struct Kara128 *kIn) {
  fnv64ResultHex(&result[ 0] , &kIn->d[1]);
  fnv64ResultHex(&result[16], &kIn->d[0]);
}

void fnvKara128DecIn(struct Kara128 *kOut, const char *str) {
  kOut->d[0] = 0;
  kOut->d[1] = 0;
  struct Kara128 ten;
  fnvInitKara128from64(&ten, 10);
  while (*str) {
    unsigned char c = *str;
    ++str;
    struct Kara128 cur;
    fnvInitKara128from64(&cur, c - '0');
    fnvKara128mul(kOut, &ten);
    fnvKara128add(kOut, &cur);
  }
}

