#include "include/fnv/fnvtop.h"
#include "include/fnv/libfnv.h"

void fnv32Init(uint32_t *hval) {
  *hval = 2166136261;
}

void fnv32UpdateChar(uint32_t *hval, unsigned char ch) {
  *hval ^= ch;
  *hval *= 16777619;
}

void fnv32UpdateBuffer(uint32_t *hval, void *buf, uint64_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    *hval ^= ch;
    *hval *= 16777619;
  }
}

void fnv32UpdateString(uint32_t *hval, char *str) {
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

void fnv64Init(uint64_t *hval) {
  *hval = 14695981039346656037ULL;
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

