#include <stdio.h>
#include <fnv.h>
#include <arith128.h>

#test fnv32t001_test
  uint32_t hval; char result[9];
  fnv32Init(&hval); fnv32ResultHex(result, &hval);
  ck_assert_str_eq(result, "811c9dc5");

#test fnv32t002_test
  uint32_t hval; char result[9];
  fnv32Init(&hval);
  fnv32UpdateChar(&hval, 'a');
  fnv32ResultHex(result, &hval);
  ck_assert_str_eq(result, "e40c292c");

#test fnv32t003_test
  uint32_t hval; char result[9];
  fnv32Init(&hval);
  fnv32UpdateString(&hval, "foobar");
  fnv32ResultHex(result, &hval);
  ck_assert_str_eq(result, "bf9cf968");

#test fnv32t004_test
  uint32_t hval; char result[9];
  fnv32Init(&hval);
  fnv32UpdateBuffer(&hval, "foobar", 6);
  fnv32ResultHex(result, &hval);
  ck_assert_str_eq(result, "bf9cf968");

#test fnv64t001_test
  uint64_t hval; char result[17];
  fnv64Init(&hval); fnv64ResultHex(result, &hval);
  ck_assert_str_eq(result, "cbf29ce484222325");

#test fnv64t002_test
  uint64_t hval; char result[17];
  fnv64Init(&hval);
  fnv64UpdateChar(&hval, 'a');
  fnv64ResultHex(result, &hval);
  ck_assert_str_eq(result, "af63dc4c8601ec8c");

#test fnv64t003_test
  uint64_t hval; char result[17];
  fnv64Init(&hval);
  fnv64UpdateString(&hval, "foobar");
  fnv64ResultHex(result, &hval);
  ck_assert_str_eq(result, "85944171f73967e8");

#test fnv64t004_test
  uint64_t hval; char result[17];
  fnv64Init(&hval);
  fnv64UpdateBuffer(&hval, "foobar", 6);
  fnv64ResultHex(result, &hval);
  ck_assert_str_eq(result, "85944171f73967e8");

#test fnv128t001arith_test
  struct Arith128 a;
  fnvInitArith128from64(&a, 7);
  ck_assert_int_eq(a.d[1], 0);
  ck_assert_int_eq(a.d[0], 7);

#test fnv128t002arith_test
  struct Arith128 a, b, c;
  fnvInitArith128from64(&a, 7);
  fnvInitArith128from64(&b, 8);
  c = a;
  fnvArith128add(&c, &b);
  ck_assert_int_eq(c.d[1], 0);
  ck_assert_int_eq(c.d[0], 15);

#test fnv128t003arith_test
  struct Arith128 a, b, c;
  fnvInitArith128from64(&a, 7);
  fnvInitArith128from64(&b, 8);
  c = a;
  fnvArith128mul(&c, &b);
  ck_assert_int_eq(c.d[1], 0);
  ck_assert_int_eq(c.d[0], 56);

#test fnv128t004arith_test
  struct Arith128 a;
  char result[33];
  fnvArith128DecIn(&a, "65535");
  ck_assert_int_eq(a.d[1], 0);
  ck_assert_int_eq(a.d[0], 65535);
  fnvArith128HexOut(result, &a);
  ck_assert_str_eq(result, "0000000000000000000000000000ffff");

#test fnv128t005arith_test
  struct Arith128 a;
  char result[33];
  fnvArith128DecIn(&a, "309485009821345068724781371");
  fnvArith128HexOut(result, &a);
  ck_assert_str_eq(result, "0000000001000000000000000000013b");

#test fnv128t006_test
  struct FNVHash128 hval;
  char result[33];
  fnv128Init(&hval);
  fnv128ResultHex(result, &hval);
  ck_assert_str_eq(result, "6c62272e07bb014262b821756295c58d");

#test fnv128t007_test
  char result[33];
  struct FNVHash128 hval;
  fnv128Init(&hval);
  fnv128UpdateChar(&hval, 'a');
  fnv128ResultHex(result, &hval);
  ck_assert_str_eq(result, "d228cb696f1a8caf78912b704e4a8964");

#test fnv128t008_test
  struct FNVHash128 hval;
  char result[33];
  fnv128Init(&hval);
  fnv128UpdateString(&hval, "foobar");
  fnv128ResultHex(result, &hval);
  ck_assert_str_eq(result, "343e1662793c64bf6f0d3597ba446f18");

#test fnv128t009_test
  struct FNVHash128 hval;
  char result[33];
  fnv128Init(&hval);
  fnv128UpdateString(&hval, "http://fnvhash.com/");
  fnv128ResultHex(result, &hval);
  ck_assert_str_eq(result, "86cdf6782de1589b910a92301accbd95");

#test fnv256t010_test
  struct FNVHash256 hval;
  char result[65];
  fnv256Init(&hval);
  fnv256ResultHex(result, &hval);
  ck_assert_str_eq(result, "dd268dbcaac550362d98c384c4e576ccc8b1536847b6bbb31023b4c8caee0535");

#test fnv256t011_test
  struct FNVHash256 hval;
  char result[65];
  fnv256Init(&hval);
  fnv256UpdateString(&hval, "http://fnvhash.com/");
  fnv256ResultHex(result, &hval);
  ck_assert_str_eq(result, "10a807ad5a7774be9b0d3f58aecae921b6314bb94e32366b17e34b27de9c3e45");
