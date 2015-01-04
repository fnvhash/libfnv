#ifndef __KARA128_H
#define __KARA128_H

#include <stdint.h>

struct Arith128 {
  uint64_t d[2];
};

void fnvInitArith128from64(struct Arith128 *kOut, uint64_t val);
void fnvArith128add(struct Arith128 *kOut, const struct Arith128 *kIn);
void fnvArith128mul(struct Arith128 *kOut, const struct Arith128 *kIn);
void fnvArith128xor8(struct Arith128 *kOut, unsigned char c);
void fnvArith128HexOut(char result[33], const struct Arith128 *kIn);
void fnvArith128DecIn(struct Arith128 *kOut, const char *str);

#endif
