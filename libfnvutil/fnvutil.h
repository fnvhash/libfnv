#ifndef __FNVUTIL_H
#define __FNVUTIL_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

FILE *fnvOpenFile(const char *filename);

void fnvIterateThroughFile(const char *filename,
  void (*func)(void *context, void *buf, uint64_t len), void *context);

void fnvApplyTestPattern(uint64_t howLong,
  void (*func)(void *context, void *buf, uint64_t len), void *context);


#endif
