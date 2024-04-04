#include <check.h>

#include "tests.h"

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  Suite *sl;
  SRunner *sr2;
  Suite *sc;
  SRunner *sr3;

  s = maze_suite();
  sl = solver_suite();
  sr = srunner_create(s);
  sr2 = srunner_create(sl);
  sc = cave_suite();
  sr3 = srunner_create(sc);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  srunner_run_all(sr2, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr2);
  srunner_free(sr2);

  srunner_run_all(sr3, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr3);
  srunner_free(sr3);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
