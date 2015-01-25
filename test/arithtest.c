#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <arith128.h>
#include "../libfnv/include/fnv/fnvtop.h"
#include <arith256.h>
#include <arith512.h>
#include <arith1024.h>

void read_1024_hex(uint64_t result[16], const char *str)
{
  uint64_t sixteen[16];
  fnvInit1024from64(sixteen, 16);
  fnvInit1024from64(result, 0);
  while (*str) {
    uint64_t cur[16];
    int c = *str++;
    char buf[2];
    buf[0] = c; buf[1] = 0;
    int retval = sscanf(buf, "%x", &c);
    uint64_t c64 = c;
    fnvInit1024from64(cur, c64);
    if (retval != 1) {
      fprintf(stderr, "sscanf %%x read_1024_hex error.\n");
      exit(1);
    }
    fnvMul1024(result, sixteen);
    fnvAdd1024(result, cur);
  }
}

void read_512_hex(uint64_t result[8], const char *str)
{
  uint64_t sixteen[8];
  fnvInit512from64(sixteen, 16);
  fnvInit512from64(result, 0);
  while (*str) {
    uint64_t cur[8];
    int c = *str++;
    char buf[2];
    buf[0] = c; buf[1] = 0;
    int retval = sscanf(buf, "%x", &c);
    uint64_t c64 = c;
    fnvInit512from64(cur, c64);
    if (retval != 1) {
      fprintf(stderr, "sscanf %%x read_512_hex error.\n");
      exit(1);
    }
    fnvMul512(result, sixteen);
    fnvAdd512(result, cur);
  }
}

void read_256_hex(uint64_t result[4], const char *str)
{
  uint64_t sixteen[4];
  fnvInit256from64(sixteen, 16);
  fnvInit256from64(result, 0);
  while (*str) {
    uint64_t cur[4];
    int c = *str++;
    char buf[2];
    buf[0] = c; buf[1] = 0;
    int retval = sscanf(buf, "%x", &c);
    uint64_t c64 = c;
    fnvInit256from64(cur, c64);
    if (retval != 1) {
      fprintf(stderr, "sscanf %%x read_256_hex error.\n");
      exit(1);
    }
    fnvMul256(result, sixteen);
    fnvAdd256(result, cur);
  }
}


void read_128_hex(struct Arith128 *result, const char *str)
{
  struct Arith128 sixteen;
  fnvInitArith128from64(&sixteen, 16);
  fnvInitArith128from64(result, 0);
  while (*str) {
    struct Arith128 cur;
    int c = *str++;
    char buf[2];
    buf[0] = c; buf[1] = 0;
    int retval = sscanf(buf, "%x", &c);
    uint64_t c64 = c;
    fnvInitArith128from64(&cur, c64);
    if (retval != 1) {
      fprintf(stderr, "sscanf %%x read_128_hex error.\n");
      exit(1);
    }
    fnvArith128mul(result, &sixteen);
    fnvArith128add(result, &cur);
  }
}

void read_64_hex(uint64_t *result, const char *str)
{
  uint64_t sixteen = 16;
  *result = 0;
  while (*str) {
    uint64_t cur;
    int c = *str++;
    char buf[2];
    buf[0] = c; buf[1] = 0;
    int retval = sscanf(buf, "%x", &c);
    if (retval != 1) {
      fprintf(stderr, "sscanf %%x read_64_hex error.\n");
      exit(1);
    }
    cur = c;
    *result *= sixteen;
    *result += cur;
  }
}

void do_test(int is_adder, int is_mult, int bits, const char *leftstr,
                                                  const char *rightstr) {
  if (bits == 16) {
    int left, right, mask = (1 << bits) - 1, result;
    sscanf(leftstr, "%x", &left);
    sscanf(rightstr, "%x", &right);
    if (is_adder) {
      result = (left + right) & mask;
    }
    if (is_mult) {
      result = (left * right) & mask;
    }
    printf("%04x\n", result);
    exit(0);
  }
  if (bits == 32) {
    uint32_t left, right, mask = (1 << bits) - 1, result;
    sscanf(leftstr, "%x", &left);
    sscanf(rightstr, "%x", &right);
    if (is_adder) {
      result = (left + right) & mask;
    }
    if (is_mult) {
      result = (left * right) & mask;
    }
    printf("%08x\n", result);
    exit(0);
  }
  if (bits == 64) {
    uint64_t left=0, right=0, result;
    read_64_hex(&left,leftstr);
    read_64_hex(&right,rightstr);
    if (is_adder) {
      result = (left + right);
    }
    if (is_mult) {
      result = (left * right);
    }
    uint32_t *smres = (uint32_t *) &result;
    printf("%08x%08x\n", smres[1], smres[0]);
    exit(0);
  }
  if (bits == 128) {
    struct Arith128 left, right, result;
    read_128_hex(&left,leftstr);
    read_128_hex(&right,rightstr);
    result = left;
    if (is_adder) {
      fnvArith128add(&result, &right);
    }
    if (is_mult) {
      fnvArith128mul(&result, &right);
    }
    char buf[33];
    fnvArith128HexOut(buf, (struct Arith128 *) &result);
    printf("%s\n", buf);
    exit(0);
  }
  if (bits == 256) {
    uint64_t left[4], right[4];
    struct FNVHash256 result;
    read_256_hex(left,leftstr);
    read_256_hex(right,rightstr);
    memcpy(&result, left, 4*sizeof(uint64_t));
    if (is_adder) {
      fnvAdd256((uint64_t *) &result, right);
    }
    if (is_mult) {
      fnvMul256((uint64_t *) &result, right);
    }
    char buf[65];
    fnv256ResultHex(buf, &result);
    printf("%s\n", buf);
    exit(0);
  }
  if (bits == 512) {
    uint64_t left[8], right[8];
    struct FNVHash512 result;
    read_512_hex(left,leftstr);
    read_512_hex(right,rightstr);
    memcpy(&result, left, sizeof(result));
    if (is_adder) {
      fnvAdd512((uint64_t *) &result, right);
    }
    if (is_mult) {
      fnvMul512((uint64_t *) &result, right);
    }
    char buf[129];
    fnv512ResultHex(buf, &result);
    printf("%s\n", buf);
    exit(0);
  }
  if (bits == 1024) {
    uint64_t left[16], right[16];
    struct FNVHash1024 result;
    read_1024_hex(left,leftstr);
    read_1024_hex(right,rightstr);
    memcpy(&result, left, 16*sizeof(uint64_t));
    if (is_adder) {
      fnvAdd1024((uint64_t *) &result, right);
    }
    if (is_mult) {
      fnvMul1024((uint64_t *) &result, right);
    }
    char buf[257];
    fnv1024ResultHex(buf, &result);
    printf("%s\n", buf);
    exit(0);
  }
}

int main(int argc, char **argv)
{
  const char *bitsstr = argv[1];
  if (bitsstr == NULL) {
    fprintf(stderr, "Must specify bits.\n");
    exit(1);
  }
  int bits = atoi(bitsstr);
  if (bits != 16 && bits != 32 && bits != 64 && bits != 128 && bits != 256 &&
      bits != 512 && bits != 1024) {
    fprintf(stderr, "invalid bits specification.\n");
    exit(1);
  }
  const char *op = argv[2];
  if (op == NULL) {
    fprintf(stderr, "Must specify operation.\n");
    exit(1);
  }
  int is_adder = 0, is_mult = 0;
  if (strcmp(op, "add") == 0) {
    is_adder = 1;
  }
  if (strcmp(op, "mul") == 0) {
    is_mult = 1;
  }
  if (is_adder == 0 && is_mult == 0) {
    fprintf(stderr, "Must specify add or mult\n");
    exit(1);
  }
  const char *left = argv[3];
  if (left == NULL) {
    printf("Must specify left operand.\n");
    exit(1);
  }
  const char *right = argv[4];
  if (right == NULL) {
    printf("Must specify right operand.\n");
    exit(1);
  }
  do_test(is_adder, is_mult, bits, left, right);
  return 0;
}
