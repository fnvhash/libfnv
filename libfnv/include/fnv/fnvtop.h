#ifndef __FNVTOP_H
#define __FNVTOP_H

#include <stdint.h>
#include <string.h>

void fnv32Init(uint32_t *hval);
void fnv32UpdateChar(uint32_t *hval, unsigned char ch);
void fnv32UpdateBuffer(uint32_t *hval, void *buf, uint64_t len);
void fnv32UpdateString(uint32_t *hval, char *buf);
uint32_t fnv32ResultUInt32(const uint32_t *hval);
void fnv32ResultHex(char result[9], const uint32_t *hval);

void fnv64Init(uint64_t *hval);
void fnv64UpdateChar(uint64_t *hval, unsigned char ch);
void fnv64UpdateBuffer(uint64_t *hval, void *buf, uint64_t len);
void fnv64UpdateString(uint64_t *hval, char *buf);
uint64_t fnv64ResultUInt64(const uint64_t *hval);
void fnv64ResultHex(char result[17], const uint64_t *hval);

#endif
