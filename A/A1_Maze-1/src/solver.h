#ifndef SOLVER_H
#define SOLVER_H

#include "maze.h"

typedef struct {
  int x, y;
} Point;

bool find_path(Maze *maze, Point *path, int *path_length, int start_row,
               int start_col, int end_row, int end_col, bool **visited);
bool solve_maze(const char *filename, int start_row, int start_col, int end_row,
                int end_col);

#endif