#ifndef __FNVTOP_H
#define __FNVTOP_H

#include <stdint.h>
#include <string.h>

void fnv32UpdateString(uint32_t *hval, const char *buf);
uint32_t fnv32ResultUInt32(const uint32_t *hval);
void fnv32ResultHex(char result[9], const uint32_t *hval);

uint64_t fnv64ResultUInt64(const uint64_t *hval);
void fnv64ResultHex(char result[17], const uint64_t *hval);

void fnv128Init(uint64_t hval[2]);
void fnv128UpdateChar(uint64_t hval[2], unsigned char ch);
void fnv128UpdateBuffer(uint64_t hval[2], const void *buf, uint64_t len);
void fnv128UpdateString(uint64_t hval[2], const char *str);
void fnv128ResultHex(char result[33], const uint64_t hval[2]);

void fnv256Init(uint64_t hval[4]);
void fnv256UpdateChar(uint64_t hval[4], unsigned char ch);
void fnv256UpdateBuffer(uint64_t hval[4], const void *buf, uint64_t len);
void fnv256UpdateString(uint64_t hval[4], const char *str);
void fnv256ResultHex(char result[65], const uint64_t hval[4]);

#endif
