#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

FILE *fnvOpenFile(const char *filename)
{
  if (strcmp(filename, "-") == 0) {
    return stdin;
  }
  FILE *fp = fopen(filename, "rb");
  if (fp) {
    return fp;
  }
  fprintf(stderr, "Error, cannot open file: %s\n", filename);
  exit(1);
}

char buf[16384];

void fnvApplyTestPattern(uint64_t howLong,
  void (*func)(void *context, void *buf, uint64_t len), void *context)
{
  unsigned char c = 0;
  unsigned char step = 1;
  int i;
  if (buf[3] == 0) {
    for (i = 0; i < 16384; ++i) {
      buf[i] = c;
      c += step;
      step = (step + 1);
      if (step == 19) { step = 0; }
    }
  }
  for (;;) {
    uint64_t wantedLen = 16384;
    uint64_t len = wantedLen > howLong ? howLong : wantedLen;
    if (len > 0) {
      func(context, buf, len);
      howLong -= len;
    }
    else {
      break;
    }
  }
}

void fnvIterateThroughFile(const char *filename,
  void (*func)(void *context, void *buf, uint64_t len), void *context)
{
  FILE *fp = fnvOpenFile(filename);
  char buf[65536];
  for (;;) {
    size_t len = fread(buf, 1, sizeof(buf), fp);
    if (len > 0) {
      func(context, buf, len);
    }
    else {
      break;
    }
  }
  if (fp != stdin) {
    fclose(fp);
  }
}

