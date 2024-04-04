#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

typedef struct Maze {
  int rows;
  int cols;
  bool **v_walls;
  bool **h_walls;
} Maze;

bool load_maze(const char *filename, Maze *maze);
bool display_maze(const char *filename);
void free_maze(Maze *maze);

#endif