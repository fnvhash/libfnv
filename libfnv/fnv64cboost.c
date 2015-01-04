#include <stdint.h>
#include <string.h>

uint64_t fnv64boost(unsigned char *buf, uint64_t len, uint64_t hval);

void fnv64UpdateChar(uint64_t *hval, unsigned char ch) {
  *hval = fnv64boost(&ch, 1, *hval);
}

void fnv64UpdateBuffer(uint64_t *hval, void *buf, size_t len) {
  *hval = fnv64boost(buf, len, *hval);
}

void fnv64UpdateString(uint64_t *hval, char *str) {
  fnv64UpdateBuffer(hval, str, strlen(str));
}

