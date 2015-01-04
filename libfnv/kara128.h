#ifndef __KARA128_H
#define __KARA128_H

#include <stdint.h>

struct Kara128 {
  uint64_t d[2];
};

void fnvInitKara128from64(struct Kara128 *kOut, uint64_t val);
void fnvKara128add(struct Kara128 *kOut, const struct Kara128 *kIn);
void fnvKara128mul(struct Kara128 *kOut, const struct Kara128 *kIn);
void fnvKara128xor8(struct Kara128 *kOut, unsigned char c);
void fnvKara128HexOut(char result[33], const struct Kara128 *kIn);
void fnvKara128DecIn(struct Kara128 *kOut, const char *str);

#endif
