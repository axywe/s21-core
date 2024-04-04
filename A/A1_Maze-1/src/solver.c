#include "solver.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool find_path(Maze *maze, Point *path, int *path_length, int start_row,
               int start_col, int end_row, int end_col, bool **visited) {
  if (start_row == end_row && start_col == end_col) {
    path[*path_length].x = start_col;
    path[*path_length].y = start_row;
    (*path_length)++;
    return true;
  }
  if (start_row < 0 || start_col < 0 || start_row >= maze->rows ||
      start_col >= maze->cols || visited[start_row][start_col])
    return false;

  visited[start_row][start_col] = true;

  // Move right
  if (start_col < maze->cols - 1 && !maze->v_walls[start_row][start_col] &&
      find_path(maze, path, path_length, start_row, start_col + 1, end_row,
                end_col, visited)) {
    path[*path_length].x = start_col;
    path[*path_length].y = start_row;
    (*path_length)++;
    return true;
  }

  // Move down
  if (start_row < maze->rows - 1 && !maze->h_walls[start_row + 1][start_col] &&
      find_path(maze, path, path_length, start_row + 1, start_col, end_row,
                end_col, visited)) {
    path[*path_length].x = start_col;
    path[*path_length].y = start_row;
    (*path_length)++;
    return true;
  }

  // Move left
  if (start_col > 0 && !maze->v_walls[start_row][start_col - 1] &&
      find_path(maze, path, path_length, start_row, start_col - 1, end_row,
                end_col, visited)) {
    path[*path_length].x = start_col;
    path[*path_length].y = start_row;
    (*path_length)++;
    return true;
  }

  // Move up
  if (start_row > 0 && !maze->h_walls[start_row][start_col] &&
      find_path(maze, path, path_length, start_row - 1, start_col, end_row,
                end_col, visited)) {
    path[*path_length].x = start_col;
    path[*path_length].y = start_row;
    (*path_length)++;
    return true;
  }

  return false;
}

bool display_solution(const char *filename, Point *path, int path_length) {
  Maze maze;
  if (!load_maze(filename, &maze)) {
    printf("Failed to load maze from %s\n", filename);
    return false;
  }

  // Create a 2D array to mark the solution path
  bool **solution = malloc(maze.rows * sizeof(bool *));
  for (int i = 0; i < maze.rows; i++) {
    solution[i] = calloc(maze.cols, sizeof(bool));
  }

  // Mark the solution path
  for (int i = 0; i < path_length; i++) {
    solution[path[i].y][path[i].x] = true;
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
      printf(solution[i][j] ? " A " : "   ");  // Mark solution with "A"
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

  // Cleanup
  for (int i = 0; i < maze.rows; i++) {
    free(solution[i]);
  }
  free(solution);
  free_maze(&maze);
  return true;
}

bool solve_maze(const char *filename, int start_row, int start_col, int end_row,
                int end_col) {
  Maze maze;
  if (!load_maze(filename, &maze)) {
    printf("Failed to load maze\n");
    return false;
  }

  bool **visited = malloc(maze.rows * sizeof(bool *));
  Point *path = malloc(maze.rows * maze.cols * sizeof(Point));
  int path_length = 0;

  for (int i = 0; i < maze.rows; i++) {
    visited[i] = calloc(maze.cols, sizeof(bool));
  }

  bool found = find_path(&maze, path, &path_length, start_row, start_col,
                         end_row, end_col, visited);

  if (found) {
    display_solution(filename, path, path_length);
  } else {
    printf("No path found.\n");
  }

  for (int i = 0; i < maze.rows; i++) {
    free(visited[i]);
  }
  free(visited);
  free(path);
  free_maze(&maze);

  return found;
}
