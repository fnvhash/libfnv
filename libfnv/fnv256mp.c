#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"
#include "arith256.h"
#include "ifnv.h"

uint64_t fnv256_offset[4], fnv256_prime[4];

void fnvKara256DecIn(uint64_t kOut[4], const char *str);

static void initParameters(void) {
  fnvKara256DecIn(fnv256_offset, "100029257958052580907070968620625704837092796014241193945225284501741471925557");
  fnvKara256DecIn(fnv256_prime, "374144419156711147060143317175368453031918731002211");
}

void fnvKara256DecIn(uint64_t kOut[4], const char *str) {
  uint64_t ten[4];
  memset(kOut, 0, 32);
  fnvInit256from64(ten, 10);
  while (*str) {
    unsigned char c = *str;
    ++str;
    uint64_t cur[4];
    fnvInit256from64(cur, c - '0');
    fnvMul256(kOut, ten);
    fnvAdd256(kOut, cur);
  }
}

void fnv256Init(struct FNVHash256 *hval) {
  if (fnv256_offset[0] == 0) {
    initParameters();
  }
  memcpy(hval, fnv256_offset, 32);
}

void fnv256UpdateChar(struct FNVHash256 *hval, unsigned char ch) {
  uint64_t k[4];
  if (fnv256_offset[0] == 0) {
    initParameters();
  }
  memcpy(k, hval, 32);
  fnv256xor8(k, ch);
  fnvMul256(k, fnv256_prime);
  memcpy(hval, k, 32);
}

void fnv256UpdateBuffer(struct FNVHash256 *hval, const void *buf, uint64_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv256UpdateChar(hval, ch);
  }
}

void fnv256UpdateString(struct FNVHash256 *hval, const char *str) {
  fnv256UpdateBuffer(hval, str, strlen(str));
}

void fnv256ResultHex(char result[65], const struct FNVHash256 *hval) {
  fnvGenericResultHex(result, 4, (const uint64_t *) hval);
}

