#include <check.h>
#include <stdio.h>

#include "../cave.h"

#define TEST_ROWS 5
#define TEST_COLS 5

bool compare_caves(bool cave1[MAX_ROWS][MAX_COLS],
                   bool cave2[MAX_ROWS][MAX_COLS]) {
  for (int i = 0; i < TEST_ROWS; ++i) {
    for (int j = 0; j < TEST_COLS; ++j) {
      if (cave1[i][j] != cave2[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void copy_test_cave_to_cave(bool test_cave[TEST_ROWS][TEST_COLS],
                            bool cave[MAX_ROWS][MAX_COLS]) {
  memset(cave, 0, sizeof(bool) * MAX_ROWS * MAX_COLS);
  for (int i = 0; i < TEST_ROWS; ++i) {
    for (int j = 0; j < TEST_COLS; ++j) {
      cave[i][j] = test_cave[i][j];
    }
  }
}

START_TEST(test_count_alive_neighbors) {
  bool test_cave[TEST_ROWS][TEST_COLS] = {{0, 0, 0, 0, 0},
                                          {0, 1, 1, 1, 0},
                                          {0, 1, 0, 1, 0},
                                          {0, 1, 1, 1, 0},
                                          {0, 0, 0, 0, 0}};

  bool cave[MAX_ROWS][MAX_COLS];
  copy_test_cave_to_cave(test_cave, cave);

  int count = count_alive_neighbors(cave, 2, 2, MAX_ROWS, MAX_COLS);
  ck_assert_int_eq(count, 8);
}
END_TEST

START_TEST(test_simulation_step) {
  bool test_initial_cave[TEST_ROWS][TEST_COLS] = {{0, 0, 0, 0, 0},
                                                  {0, 1, 1, 1, 0},
                                                  {0, 1, 0, 1, 0},
                                                  {0, 1, 1, 1, 0},
                                                  {0, 0, 0, 0, 0}};

  bool expected_cave[TEST_ROWS][TEST_COLS] = {{1, 1, 1, 1, 1},
                                              {1, 0, 1, 0, 0},
                                              {1, 1, 1, 1, 0},
                                              {1, 0, 1, 0, 0},
                                              {1, 0, 0, 0, 0}};

  bool cave[MAX_ROWS][MAX_COLS];
  bool newCave[MAX_ROWS][MAX_COLS];
  bool tempExpectedCave[MAX_ROWS][MAX_COLS];

  copy_test_cave_to_cave(test_initial_cave, cave);
  copy_test_cave_to_cave(expected_cave, tempExpectedCave);

  simulation_step(cave, newCave, MAX_ROWS, MAX_COLS, 3, 3);

  bool result = compare_caves(tempExpectedCave, newCave);
  ck_assert(result);
}
END_TEST

Suite *cave_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Cave");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_count_alive_neighbors);
  tcase_add_test(tc_core, test_simulation_step);
  suite_add_tcase(s, tc_core);

  return s;
}