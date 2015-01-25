#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"
#include "arith128.h"
#include "ifnv.h"

struct Arith128 fnv128_offset, fnv128_prime;

static void initParameters(void) {
  fnvArith128DecIn(&fnv128_offset, "144066263297769815596495629667062367629");
  fnvArith128DecIn(&fnv128_prime, "309485009821345068724781371");
}

void fnv128Init(struct FNVHash128 *hval) {
  if (fnv128_offset.d[0] == 0) {
    initParameters();
  }
  hval->_x[0] = fnv128_offset.d[0];
  hval->_x[1] = fnv128_offset.d[1];
}

void fnv128UpdateChar(struct FNVHash128 *hval, unsigned char ch) {
  struct Arith128 k;
  if (fnv128_offset.d[0] == 0) {
    initParameters();
  }
  k.d[0] = hval->_x[0];
  k.d[1] = hval->_x[1];
  fnvArith128xor8(&k, ch);
  fnvArith128mul(&k, &fnv128_prime);
  hval->_x[0] = k.d[0];
  hval->_x[1] = k.d[1];
}

void fnv128UpdateBuffer(struct FNVHash128 *hval, const void *buf, uint64_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv128UpdateChar(hval, ch);
  }
}

void fnv128UpdateString(struct FNVHash128 *hval, const char *str) {
  fnv128UpdateBuffer(hval, str, strlen(str));
}

void fnv128ResultHex(char result[33], const struct FNVHash128 *hval) {
  fnvGenericResultHex(result, 2, (uint64_t *) hval);
}

