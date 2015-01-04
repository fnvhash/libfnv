#include <stdio.h>
#include <fnv.h>
#include <fnvutil.h>

#test fnv32t001_test
  FILE *fp = fnvOpenFile("libfnv/include/fnv.h");
  ck_assert(fp != NULL);

