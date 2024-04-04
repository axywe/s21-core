#include "maze.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool load_maze(const char *filename, Maze *maze) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    return false;
  }

  fscanf(file, "%d %d", &maze->rows, &maze->cols);

  maze->v_walls = malloc(maze->rows * sizeof(bool *));
  maze->h_walls = malloc((maze->rows + 1) * sizeof(bool *));
  for (int i = 0; i < maze->rows; i++) {
    maze->v_walls[i] = malloc((maze->cols - 1) * sizeof(bool));
    for (int j = 0; j < maze->cols - 1; j++) {
      int wall;
      fscanf(file, "%d", &wall);
      maze->v_walls[i][j] = wall;
    }
  }
  for (int i = 0; i <= maze->rows; i++) {
    maze->h_walls[i] = malloc(maze->cols * sizeof(bool));
    for (int j = 0; j < maze->cols; j++) {
      int wall;
      fscanf(file, "%d", &wall);
      maze->h_walls[i][j] = wall;
    }
  }

  fclose(file);
  return true;
}

bool display_maze(const char *filename) {
  Maze maze;
  if (!load_maze(filename, &maze)) {
    printf("Failed to load maze from %s\n", filename);
    return false;
  }

  // Top border
  for (int j = 0; j < maze.cols; j++) {
    printf("+---");
  }
  printf("+\n");

  for (int i = 0; i < maze.rows; i++) {
    // Left border
    printf("|");
    for (int j = 0; j < maze.cols; j++) {
      printf("   ");
      if (j < maze.cols - 1) {
        printf(maze.v_walls[i][j] ? "|" : " ");
      }
    }
    // Right border
    printf("|\n");

    // Bottom border
    for (int j = 0; j < maze.cols; j++) {
      printf("+");
      printf(maze.h_walls[i + 1][j] ? "---" : "   ");
    }
    printf("+\n");
  }

  free_maze(&maze);
  return true;
}

void free_maze(Maze *maze) {
  for (int i = 0; i < maze->rows; i++) {
    free(maze->v_walls[i]);
  }
  free(maze->v_walls);

  for (int i = 0; i <= maze->rows; i++) {
    free(maze->h_walls[i]);
  }
  free(maze->h_walls);
}
