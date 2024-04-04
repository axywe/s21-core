#include "generator.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_maze(Maze *maze) {
  for (int i = 0; i < maze->rows; ++i) {
    for (int j = 0; j < maze->cols - 1; ++j) {
      maze->v_walls[i][j] = true;
    }
  }
  for (int i = 0; i <= maze->rows; ++i) {
    for (int j = 0; j < maze->cols; ++j) {
      maze->h_walls[i][j] = i == 0 || i == maze->rows;
    }
  }
}

void carve_maze(Maze *maze) {
  srand((unsigned int)time(NULL));

  int set[maze->cols];
  int next_set = 1;

  // Initialize sets for the first row
  for (int j = 0; j < maze->cols; ++j) {
    set[j] = next_set++;
  }

  for (int i = 0; i < maze->rows; ++i) {
    // Join sets horizontally
    for (int j = 0; j < maze->cols - 1; ++j) {
      if ((rand() % 2 == 0 || i == maze->rows - 1) && set[j] != set[j + 1]) {
        maze->v_walls[i][j] = false;
        int old_set = set[j + 1];
        for (int k = 0; k < maze->cols; ++k) {
          if (set[k] == old_set) {
            set[k] = set[j];
          }
        }
      }
    }

    if (i < maze->rows - 1) {
      // Reset all horizontal walls to true for the next row
      for (int j = 0; j < maze->cols; ++j) {
        maze->h_walls[i + 1][j] = true;
      }

      // Create vertical openings
      for (int j = 0; j < maze->cols; ++j) {
        if (rand() % 2 == 0) {
          maze->h_walls[i + 1][j] = false;
        }
      }

      // Ensure at least one vertical opening for each set
      for (int s = 1; s <= next_set; s++) {
        bool set_has_opening = false;
        for (int j = 0; j < maze->cols; j++) {
          if (set[j] == s && !maze->h_walls[i + 1][j]) {
            set_has_opening = true;
            break;
          }
        }
        if (!set_has_opening) {
          for (int j = 0; j < maze->cols; j++) {
            if (set[j] == s) {
              maze->h_walls[i + 1][j] = false;
              break;
            }
          }
        }
      }

      // Prepare sets for the next row
      for (int j = 0; j < maze->cols; j++) {
        if (maze->h_walls[i + 1][j]) {
          set[j] = next_set++;
        }
      }
    } else {
      // Last row: ensure all cells are part of the same set
      for (int j = 0; j < maze->cols - 1; ++j) {
        if (set[j] != set[j + 1]) {
          maze->v_walls[i][j] = false;
          int old_set = set[j + 1];
          for (int k = 0; k < maze->cols; ++k) {
            if (set[k] == old_set) {
              set[k] = set[j];
            }
          }
        }
      }
    }
  }
}

bool generate_maze(int rows, int cols, const char *filename) {
  Maze maze;
  maze.rows = rows;
  maze.cols = cols;
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

  FILE *file = fopen(filename, "w");
  if (!file) {
    free_maze(&maze);
    return false;
  }
  fprintf(file, "%d %d\n", maze.rows, maze.cols);
  for (int i = 0; i < maze.rows; i++) {
    for (int j = 0; j < maze.cols - 1; j++) {
      fprintf(file, "%d ", maze.v_walls[i][j]);
    }
    fprintf(file, "\n");
  }
  for (int i = 0; i <= maze.rows; i++) {
    for (int j = 0; j < maze.cols; j++) {
      fprintf(file, "%d ", maze.h_walls[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
  free_maze(&maze);

  return true;
}
