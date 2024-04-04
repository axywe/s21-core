#include <check.h>
#include <stdlib.h>

#include "tests.h"

START_TEST(test_initialize_maze) {
  Maze maze;
  maze.rows = 5;
  maze.cols = 5;
  maze.v_walls = malloc(maze.rows * sizeof(bool *));
  maze.h_walls = malloc((maze.rows + 1) * sizeof(bool *));
  for (int i = 0; i < maze.rows; i++) {
    maze.v_walls[i] = malloc((maze.cols - 1) * sizeof(bool));
  }
  for (int i = 0; i <= maze.rows; i++) {
    maze.h_walls[i] = malloc(maze.cols * sizeof(bool));
  }

  initialize_maze(&maze);

  // Assert that all vertical walls are initialized to true
  for (int i = 0; i < maze.rows; ++i) {
    for (int j = 0; j < maze.cols - 1; ++j) {
      ck_assert(maze.v_walls[i][j]);
    }
  }

  free_maze(&maze);
}
END_TEST

START_TEST(test_carve_maze) {
  // We can't predict the exact outcome of carve_maze(),
  // but we can check if it has properly modified the maze.
  Maze maze;
  maze.rows = 5;
  maze.cols = 5;
  maze.v_walls = malloc(maze.rows * sizeof(bool *));
  maze.h_walls = malloc((maze.rows + 1) * sizeof(bool *));
  for (int i = 0; i < maze.rows; i++) {
    maze.v_walls[i] = malloc((maze.cols - 1) * sizeof(bool));
  }
  for (int i = 0; i <= maze.rows; i++) {
    maze.h_walls[i] = malloc(maze.cols * sizeof(bool));
  }

  initialize_maze(&maze);
  carve_maze(&maze);

  // We can just check if the walls have been modified in some way
  bool wall_modified = false;
  for (int i = 0; i < maze.rows; ++i) {
    for (int j = 0; j < maze.cols - 1; ++j) {
      if (maze.v_walls[i][j] == false) {
        wall_modified = true;
        break;
      }
    }
  }
  for (int i = 0; i <= maze.rows; ++i) {
    for (int j = 0; j < maze.cols; ++j) {
      if (maze.h_walls[i][j] == false) {
        wall_modified = true;
        break;
      }
    }
  }

  ck_assert(wall_modified);

  free_maze(&maze);
}
END_TEST

Suite *maze_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Maze");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_initialize_maze);
  tcase_add_test(tc_core, test_carve_maze);
  suite_add_tcase(s, tc_core);

  return s;
}
