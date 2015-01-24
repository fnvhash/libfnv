#include <fnv.h>
#include <fnvutil.h>
#include <stdio.h>

void updateHash512(void *context, void *buf, uint64_t length)
{
  struct FNVHash512 *hval = (struct FNVHash512 *) context;
  fnv512UpdateBuffer(hval, buf, length);
}

void printVersion(void)
{
  printf("fnv512 version 0.8.2\n");
}

void printHelp(void)
{
  printf("Usage:\n\nfnv512 [FILE]...\n\n"
         "With no arguments it will read from standard input.\n"
         "This command will print the FNV-1a 512-bit hash for each listed file in order.\n");
}

int main(int argc, char **argv)
{
  struct FNVHash512 hval;
  int i;
  int didSomething = 0;
  char result[129];
  int nomoreopts = 0;
  for (i = 1; i < argc; ++i) {
    char *cur = argv[i];
    if (cur[0] == '-' && !nomoreopts) {
      if (cur[1] == '-' && cur[2] == '\0') {
        nomoreopts = 1;
        continue;
      }
      if (cur[1] == 'h' || (cur[2] == 'h' && cur[1] == '-')) {
        printHelp();
        exit(0);
      }
      if (cur[1] == 'v' || (cur[2] == 'v' && cur[1] == '-')) {
        printVersion();
        exit(0);
      }
      printf("Error: unrecognized option: %s\n", cur);
      exit(1);
    }
    fnv512Init(&hval);
    fnvIterateThroughFile(cur, updateHash512, &hval);
    fnv512ResultHex(result, &hval);
    printf("%s\n", result);
    didSomething = 1;
  }
  if (!didSomething) {
    fnv512Init(&hval);
    fnvIterateThroughFile("-", updateHash512, &hval);
    fnv512ResultHex(result, &hval);
    printf("%s\n", result);
  }
  return 0;
}
