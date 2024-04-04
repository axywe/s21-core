#include <check.h>
#include <stdlib.h>

#include "tests.h"

START_TEST(test_find_path) {
  Maze maze;
  maze.rows = 3;
  maze.cols = 3;
  maze.v_walls = (bool **)malloc(maze.rows * sizeof(bool *));
  maze.h_walls = (bool **)malloc((maze.rows + 1) * sizeof(bool *));
  for (int i = 0; i < maze.rows; i++) {
    maze.v_walls[i] = (bool *)malloc((maze.cols - 1) * sizeof(bool));
  }
  for (int i = 0; i <= maze.rows; i++) {
    maze.h_walls[i] = (bool *)malloc(maze.cols * sizeof(bool));
  }

  // Initialize maze walls (example maze without walls)
  for (int i = 0; i < maze.rows; i++) {
    for (int j = 0; j < maze.cols - 1; j++) {
      maze.v_walls[i][j] = false;
    }
  }
  for (int i = 0; i <= maze.rows; i++) {
    for (int j = 0; j < maze.cols; j++) {
      maze.h_walls[i][j] = false;
    }
  }

  // Assume the start is (0,0) and end is (2,2)
  Point path[9];
  int path_length = 0;
  bool **visited = (bool **)malloc(maze.rows * sizeof(bool *));
  for (int i = 0; i < maze.rows; i++) {
    visited[i] = (bool *)calloc(maze.cols, sizeof(bool));
  }

  bool path_found = find_path(&maze, path, &path_length, 0, 0, 2, 2, visited);

  // Assert that a path is found
  ck_assert(path_found);

  // Assert that the path is of expected length
  ck_assert_int_eq(path_length, 5);

  // Clean up
  for (int i = 0; i < maze.rows; i++) {
    free(visited[i]);
  }
  free(visited);
  free_maze(&maze);
}
END_TEST

Suite *solver_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Solver");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_find_path);

  suite_add_tcase(s, tc_core);

  return s;
}
