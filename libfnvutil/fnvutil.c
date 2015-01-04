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

