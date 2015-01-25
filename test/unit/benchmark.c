#include <stdio.h>
#include <fnv.h>
#include <fnvutil.h>
#include <sys/types.h>
#include <sys/time.h>

double getTime(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


void updateHash32(void *context, void *buf, uint64_t length)
{
  uint32_t *hval = (uint32_t *) context;
  fnv32UpdateBuffer(hval, buf, length);
}

void updateHash64(void *context, void *buf, uint64_t length)
{
  uint64_t *hval = (uint64_t *) context;
  fnv64UpdateBuffer(hval, buf, length);
}

void updateHash128(void *context, void *buf, uint64_t length)
{
  struct FNVHash128 *hval = (struct FNVHash128 *) context;
  fnv128UpdateBuffer(hval, buf, length);
}

void updateHash256(void *context, void *buf, uint64_t length)
{
  struct FNVHash256 *hval = (struct FNVHash256 *) context;
  fnv256UpdateBuffer(hval, buf, length);
}

void updateHash512(void *context, void *buf, uint64_t length)
{
  struct FNVHash512 *hval = (struct FNVHash512 *) context;
  fnv512UpdateBuffer(hval, buf, length);
}

void updateHash1024(void *context, void *buf, uint64_t length)
{
  struct FNVHash1024 *hval = (struct FNVHash1024 *) context;
  fnv1024UpdateBuffer(hval, buf, length);
}


int main(int argc, char **argv)
{
  uint64_t hval64;
  struct FNVHash128 hval128;
  struct FNVHash256 hval256;
  struct FNVHash512 hval512;
  struct FNVHash1024 hval1024;
  uint32_t hval32;
  uint64_t len32=25e6;
  uint64_t len64=25e6;
  uint64_t len128=1e6;
  uint64_t len256=1e5;
  uint64_t len512=1e4;
  uint64_t len1024=1e3;
  double t032,tf32,t064,tf64,t0128,tf128,t0256,tf256,t0512,tf512,t01024,tf1024;

  t032=getTime();
  fnv32Init(&hval32);
  fnvApplyTestPattern(len32, updateHash32, &hval32);
  tf32=getTime();
  printf("FNV32:%d mb/s\n",(int) (len32 /(1e6* (tf32-t032))));

  t064=getTime();
  fnv64Init(&hval64);
  fnvApplyTestPattern(len64, updateHash64, &hval64);
  tf64=getTime();
  printf("FNV64:%d mb/s\n",(int) (len64 /(1e6* (tf64-t064))));

  fnv128Init(&hval128);
  fnvApplyTestPattern(1, updateHash128, &hval128);

  t0128=getTime();
  fnv128Init(&hval128);
  fnvApplyTestPattern(len128, updateHash128, &hval128);
  tf128=getTime();
  printf("FNV128:%d mb/s\n",(int) (len128 /(1e6* (tf128-t0128))));

  fnv256Init(&hval256);
  fnvApplyTestPattern(1, updateHash256, &hval256);

  t0256=getTime();
  fnv256Init(&hval256);
  fnvApplyTestPattern(len256, updateHash256, &hval256);
  tf256=getTime();
  printf("FNV256:%d mb/s\n",(int) (len256 /(1e6* (tf256-t0256))));

  fnv512Init(&hval512);
  fnvApplyTestPattern(1, updateHash512, &hval512);

  t0512=getTime();
  fnv512Init(&hval512);
  fnvApplyTestPattern(len512, updateHash512, &hval512);
  tf512=getTime();
  printf("FNV512:%d kb/s\n",(int) (len512*1024 /(1e6* (tf512-t0512))));


  fnv1024Init(&hval1024);
  fnvApplyTestPattern(1, updateHash1024, &hval1024);

  t01024=getTime();
  fnv1024Init(&hval1024);
  fnvApplyTestPattern(len1024, updateHash1024, &hval1024);
  tf1024=getTime();
  printf("FNV1024:%d kb/s\n",(int) (len1024*1024 /(1e6* (tf1024-t01024))));

  exit(0);
}
