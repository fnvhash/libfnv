#ifndef __LIBFNV_H
#define __LIBFNV_H

#include <stdint.h>

static __inline__ void fnv32Init(uint32_t *hval);
static __inline__ void fnv32UpdateChar(uint32_t *hval, unsigned char ch);
static __inline__ void fnv32UpdateBuffer(uint32_t *hval, const void *buf, uint64_t len);
static __inline__ void fnv64Init(uint64_t *hval);

static __inline__ void fnv64UpdateChar(uint64_t *hval, unsigned char ch);
static __inline__ void fnv64UpdateBuffer(uint64_t *hval, const void *buf, uint64_t len);

static __inline__ void fnv64Init(uint64_t *hval) {
  *hval = 14695981039346656037ULL;
}

static __inline__ void fnv32Init(uint32_t *hval) {
  *hval = 2166136261;
}

static __inline__ void fnv32UpdateChar(uint32_t *hval, unsigned char ch) {
  *hval ^= ch;
  *hval *= 16777619;
}

static __inline__ void fnv32UpdateBuffer(uint32_t *hval, const void *buf, uint64_t len) {
  uint64_t i;
  unsigned char *qbuf = (unsigned char *) buf;
  for (i = 0; i < len; ++i) {
    unsigned char ch = *qbuf++;
    *hval ^= ch;
    *hval *= 16777619;
  }
}

static __inline__ void fnv64UpdateChar(uint64_t *hval, unsigned char ch) {
  *hval ^= ch;
  *hval *= 1099511628211U;
}

static __inline__ void fnv64UpdateBuffer(uint64_t *hval, const void *buf, uint64_t len) {
  uint64_t i;
  for (i = 0; i < len; ++i) {
    unsigned char ch = ((unsigned char *) buf)[i];
    fnv64UpdateChar(hval, ch);
  }
}

static __inline__ void fnv64UpdateString(uint64_t *hval, const char *buf) {
  fnv64UpdateBuffer(hval, buf, strlen(buf));
}

#endif
