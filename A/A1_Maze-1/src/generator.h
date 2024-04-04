#ifndef GENERATOR_H
#define GENERATOR_H

#include <string.h>

#include "maze.h"

void initialize_maze(Maze *maze);
void carve_maze(Maze *maze);
bool generate_maze(int rows, int cols, const char *filename);

#endif