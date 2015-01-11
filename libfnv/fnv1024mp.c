#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"
#include "arith1024.h"

uint64_t fnv1024_offset[16], fnv1024_prime[16];

void fnvKara1024DecIn(uint64_t kOut[16], const char *str);

static void initParameters(void) {
  fnvKara1024DecIn(fnv1024_offset,"14197795064947621068722070641403218320880622795441933960878474914617582723252296732303717722150864096521202355549365628174669108571814760471015076148029755969804077320157692458563003215304957150157403644460363550505412711285966361610267868082893823963790439336411086884584107735010676915");
  fnvKara1024DecIn(fnv1024_prime, "5016456510113118655434598811035278955030765345404790744303017523831112055108147451509157692220295382716162651878526895249385292291816524375083746691371804094271873160484737966720260389217684476157468082573");
}

void fnvKara1024DecIn(uint64_t kOut[16], const char *str) {
  uint64_t ten[16];
  memset(kOut, 0, 128);
  fnvInit1024from64(ten, 10);
  while (*str) {
    unsigned char c = *str;
    ++str;
    uint64_t cur[16];
    fnvInit1024from64(cur, c - '0');
    fnvMul1024(kOut, ten);
    fnvAdd1024(kOut, cur);
  }
}

void fnv1024Init(uint64_t hval[16]) {
  if (fnv1024_offset[0] == 0) {
    initParameters();
  }
  memcpy(hval, fnv1024_offset, 128);
}

void fnv1024UpdateChar(uint64_t hval[16], unsigned char ch) {
  uint64_t k[16];
  if (fnv1024_offset[0] == 0) {
    initParameters();
  }
  memcpy(k, hval, 128);
  fnv1024xor8(k, ch);
  fnvMul1024(k, fnv1024_prime);
  memcpy(hval, k, 128);
}

void fnv1024UpdateBuffer(uint64_t hval[16], const void *buf, uint64_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv1024UpdateChar(hval, ch);
  }
}

void fnv1024UpdateString(uint64_t hval[16], const char *str) {
  fnv1024UpdateBuffer(hval, str, strlen(str));
}

static void genericResultHex1024(char *result, int howBig, const uint64_t *hval) {
  int i;
  for (i = howBig; i >= 0; i--) {
    fnv64ResultHex(result+(howBig-i)*16, &hval[i]);
  }
}

void fnv1024ResultHex(char result[257], const uint64_t hval[16]) {
  genericResultHex1024(result, 15, hval);
}

