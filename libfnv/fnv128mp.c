#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"
#include "kara128.h"

struct Kara128 fnv128_offset, fnv128_prime;

static void initParameters(void) {
  fnvKara128DecIn(&fnv128_offset, "144066263297769815596495629667062367629");
  fnvKara128DecIn(&fnv128_prime, "309485009821345068724781371");
}

void fnv128Init(uint64_t hval[2]) {
  if (fnv128_offset.d[0] == 0) {
    initParameters();
  }
  hval[0] = fnv128_offset.d[0];
  hval[1] = fnv128_offset.d[1];
}

void fnv128UpdateChar(uint64_t hval[2], unsigned char ch) {
  struct Kara128 k;
  if (fnv128_offset.d[0] == 0) {
    initParameters();
  }
  k.d[0] = hval[0];
  k.d[1] = hval[1];
  fnvKara128xor8(&k, ch);
  fnvKara128mul(&k, &fnv128_prime);
  hval[0] = k.d[0];
  hval[1] = k.d[1];
}

void fnv128UpdateBuffer(uint64_t hval[2], const void *buf, uint64_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv128UpdateChar(hval, ch);
  }
}

void fnv128UpdateString(uint64_t hval[2], const char *str) {
  fnv128UpdateBuffer(hval, str, strlen(str));
}

static void genericResultHex128(char *result, int howBig, const uint64_t *hval) {
  fnv64ResultHex(result, &hval[1]);
  fnv64ResultHex(result+16, &hval[0]);
}

void fnv128ResultHex(char result[33], const uint64_t hval[2]) {
  genericResultHex128(result, 16, hval);
}

