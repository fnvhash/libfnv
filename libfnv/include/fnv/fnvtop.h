#ifndef __FNVTOP_H
#define __FNVTOP_H

#include <stdint.h>
#include <string.h>

struct FNVHash32 {
  uint32_t _x[1];
};

struct FNVHash64 {
  uint64_t _x[1];
};

struct FNVHash128 {
  uint64_t _x[2];
};

struct FNVHash256 {
  uint64_t _x[4];
};

struct FNVHash512 {
  uint64_t _x[8];
};

struct FNVHash1024 {
  uint64_t _x[16];
};

void fnv32UpdateString(uint32_t *hval, const char *buf);
uint32_t fnv32ResultUInt32(const uint32_t *hval);
void fnv32ResultHex(char result[9], const uint32_t *hval);

uint64_t fnv64ResultUInt64(const uint64_t *hval);
void fnv64ResultHex(char result[17], const uint64_t *hval);

void fnv128Init(struct FNVHash128 *hval);
void fnv128UpdateChar(struct FNVHash128 *hval, unsigned char ch);
void fnv128UpdateBuffer(struct FNVHash128 *hval, const void *buf, uint64_t len);
void fnv128UpdateString(struct FNVHash128 *hval, const char *str);
void fnv128ResultHex(char result[33], const struct FNVHash128 *hval);

void fnv256Init(struct FNVHash256 *hval);
void fnv256UpdateChar(struct FNVHash256 *hval, unsigned char ch);
void fnv256UpdateBuffer(struct FNVHash256 *hval, const void *buf, uint64_t len);
void fnv256UpdateString(struct FNVHash256 *hval, const char *str);
void fnv256ResultHex(char result[65], const struct FNVHash256 *hval);

void fnv512Init(struct FNVHash512 *hval);
void fnv512UpdateChar(struct FNVHash512 *hval, unsigned char ch);
void fnv512UpdateBuffer(struct FNVHash512 *hval, const void *buf, uint64_t len);
void fnv512UpdateString(struct FNVHash512 *hval, const char *str);
void fnv512ResultHex(char result[129], const struct FNVHash512 *hval);

void fnv1024Init(struct FNVHash1024 *hval);
void fnv1024UpdateChar(struct FNVHash1024 *hval, unsigned char ch);
void fnv1024UpdateBuffer(struct FNVHash1024 *hval, const void *buf, uint64_t len);
void fnv1024UpdateString(struct FNVHash1024 *hval, const char *str);
void fnv1024ResultHex(char result[257], const struct FNVHash1024 *hval);
#endif
