#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"
#include "arith512.h"

uint64_t fnv512_offset[8], fnv512_prime[8];

void fnvKara512DecIn(uint64_t kOut[8], const char *str);

static void initParameters(void) {
  fnvKara512DecIn(fnv512_offset, "9659303129496669498009435400716310466090418745672637896108374329434462657994582932197716438449813051892206539805784495328239340083876191928701583869517785");
  fnvKara512DecIn(fnv512_prime, "35835915874844867368919076489095108449946327955754392558399825615420669938882575126094039892345713852759");
}

void fnvKara512DecIn(uint64_t kOut[8], const char *str) {
  uint64_t ten[8];
  memset(kOut, 0, 64);
  fnvInit512from64(ten, 10);
  while (*str) {
    unsigned char c = *str;
    ++str;
    uint64_t cur[8];
    fnvInit512from64(cur, c - '0');
    fnvMul512(kOut, ten);
    fnvAdd512(kOut, cur);
  }
}

void fnv512Init(struct FNVHash512 *hval) {
  if (fnv512_offset[0] == 0) {
    initParameters();
  }
  memcpy(hval, fnv512_offset, 64);
}

void fnv512UpdateChar(struct FNVHash512 *hval, unsigned char ch) {
  uint64_t k[8];
  if (fnv512_offset[0] == 0) {
    initParameters();
  }
  memcpy(k, hval, 64);
  fnv512xor8(k, ch);
  fnvMul512(k, fnv512_prime);
  memcpy(hval, k, 64);
}

void fnv512UpdateBuffer(struct FNVHash512 *hval, const void *buf, uint64_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv512UpdateChar(hval, ch);
  }
}

void fnv512UpdateString(struct FNVHash512 *hval, const char *str) {
  fnv512UpdateBuffer(hval, str, strlen(str));
}

static void genericResultHex512(char *result, int howBig, const uint64_t *hval) {
  int i;
  for (i = howBig; i >= 0; i--) {
    fnv64ResultHex(result+(howBig-i)*16, &hval[i]);
  }
}

void fnv512ResultHex(char result[129], const struct FNVHash512 *hval) {
  genericResultHex512(result, 7, &hval->_x[0]);
}

