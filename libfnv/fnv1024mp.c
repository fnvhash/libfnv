#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"
#include "arith1024.h"
#include "ifnv.h"

struct FNVHash1024 fnv1024_offset, fnv1024_prime;

void fnvKara1024DecIn(struct FNVHash1024 *, const char *str);

static void initParameters(void) {
  fnvKara1024DecIn(&fnv1024_offset,"14197795064947621068722070641403218320880622795441933960878474914617582723252296732303717722150864096521202355549365628174669108571814760471015076148029755969804077320157692458563003215304957150157403644460363550505412711285966361610267868082893823963790439336411086884584107735010676915");
  fnvKara1024DecIn(&fnv1024_prime, "5016456510113118655434598811035278955030765345404790744303017523831112055108147451509157692220295382716162651878526895249385292291816524375083746691371804094271873160484737966720260389217684476157468082573");
}

void fnvKara1024DecIn(struct FNVHash1024 *kOut, const char *str) {
  struct FNVHash1024 ten;
  memset(kOut, 0, 128);
  fnvInit1024from64((uint64_t *) &ten, 10);
  while (*str) {
    unsigned char c = *str;
    ++str;
    uint64_t cur[16];
    fnvInit1024from64(cur, c - '0');
    fnvMul1024((uint64_t *) kOut, (uint64_t *) &ten);
    fnvAdd1024((uint64_t *) kOut, cur);
  }
}

void fnv1024Init(struct FNVHash1024 *hval) {
  if (((uint64_t *) &fnv1024_offset)[0] == 0) {
    initParameters();
  }
  memcpy(hval, &fnv1024_offset, 128);
}

void fnv1024UpdateChar(struct FNVHash1024 *hval, unsigned char ch) {
  struct FNVHash1024 k;
  if (((uint64_t *) &fnv1024_offset)[0] == 0) {
    initParameters();
  }
  memcpy(&k, hval, 128);
  fnv1024xor8((uint64_t *) &k, ch);
  fnvMul1024((uint64_t *) &k,(uint64_t *)  &fnv1024_prime);
  memcpy(hval, &k, 128);
}

void fnv1024UpdateBuffer(struct FNVHash1024 *hval, const void *buf, uint64_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv1024UpdateChar(hval, ch);
  }
}

void fnv1024UpdateString(struct FNVHash1024 *hval, const char *str) {
  fnv1024UpdateBuffer(hval, str, strlen(str));
}

void fnv1024ResultHex(char result[257], const struct FNVHash1024 *hval) {
  fnvGenericResultHex(result, 16, (const uint64_t *) hval);
}

