#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint64_t fnv64a(unsigned char *buf, uint64_t len, uint64_t hval);

#define FNV64_1A_INIT 0xcbf29ce484222325ULL

int main(int argc, char **argv)
{
  unsigned char *buf = (unsigned char *) "foobar";
  uint64_t result;

  result = fnv64a(buf, 6, FNV64_1A_INIT);
  exit(result != 0x85944171f73967e8);
}
