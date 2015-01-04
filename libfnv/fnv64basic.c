#include <stdint.h>
#include <string.h>

void fnv64UpdateChar(uint64_t *hval, unsigned char ch) {
  *hval ^= ch;
  *hval *= 1099511628211U;
}

void fnv64UpdateBuffer(uint64_t *hval, void *buf, size_t len) {
  size_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv64UpdateChar(hval, ch);
  }
}

void fnv64UpdateString(uint64_t *hval, char *str) {
  fnv64UpdateBuffer(hval, str, strlen(str));
}

