#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"

void fnv32UpdateString(uint32_t *hval, const char *str) {
  fnv32UpdateBuffer(hval, str, strlen(str));
}

uint32_t fnv32ResultUInt32(const uint32_t *hval) {
  return *hval;
}

static void genericResultHex32(char *result, int howBig, const uint32_t *hval) {
  int i;
  const static char *hex = "0123456789abcdef";
  uint32_t c = *hval;
  for (i = howBig-1; i >= 0; --i) {
    uint32_t n = c & 0xff;
    c >>= 8;
    result[2*i] = hex[n >> 4];
    result[2*i+1] = hex[n & 0x0f];
  }
  result[2*howBig] = '\0';
}

void fnv32ResultHex(char result[9], const uint32_t *hval) {
  genericResultHex32(result, 4, hval);
}

uint64_t fnv64ResultUInt64(const uint64_t *hval) {
  return *hval;
}

static void genericResultHex64(char *result, int howBig, const uint64_t *hval) {
  int i;
  const static char *hex = "0123456789abcdef";
  uint64_t c = *hval;
  for (i = howBig-1; i >= 0; --i) {
    uint64_t n = c & 0xff;
    c >>= 8;
    result[2*i] = hex[n >> 4];
    result[2*i+1] = hex[n & 0x0f];
  }
  result[2*howBig] = '\0';
}

void fnv64ResultHex(char result[17], const uint64_t *hval) {
  genericResultHex64(result, 8, hval);
}

void fnvGenericResultHex(char *result, int howBig, const uint64_t *hval) {
  int i;
  for (i = 0; i < howBig; i++) {
    fnv64ResultHex(result+i*16, &hval[howBig-i-1]);
  }
}
