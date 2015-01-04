#include <stdio.h>
#include <fnv.h>

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

