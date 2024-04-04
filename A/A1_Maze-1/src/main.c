#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cave.h"
#include "generator.h"
#include "maze.h"
#include "solver.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s <command> [options]\n", argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "generate") == 0) {
    if (argc != 5) {
      printf("Usage: %s generate <rows> <cols> <filename>\n", argv[0]);
      return 1;
    }

    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);
    const char* filename = argv[4];

    if (!generate_maze(rows, cols, filename)) {
      fprintf(stderr, "Error generating maze.\n");
      return 1;
    }
    display_maze(filename);
    printf("Maze generated and saved to %s\n", filename);
  } else if (strcmp(argv[1], "solve") == 0) {
    if (argc != 7) {
      printf(
          "Usage: %s solve <filename> <start_row> <start_col> <end_row> "
          "<end_col>\n",
          argv[0]);
      return 1;
    }

    const char* filename = argv[2];
    int start_row = atoi(argv[3]);
    int start_col = atoi(argv[4]);
    int end_row = atoi(argv[5]);
    int end_col = atoi(argv[6]);

    if (!solve_maze(filename, start_row, start_col, end_row, end_col)) {
      fprintf(stderr, "Error solving maze.\n");
      return 1;
    }
    printf("Maze solution displayed.\n");
  } else if (strcmp(argv[1], "display") == 0) {
    if (argc != 3) {
      printf("Usage: %s display <filename>\n", argv[0]);
      return 1;
    }

    const char* filename = argv[2];

    if (!display_maze(filename)) {
      fprintf(stderr, "Error displaying maze.\n");
      return 1;
    }
    printf("Maze displayed.\n");
  } else if (strcmp(argv[1], "cave") == 0) {
    if (argc != 7) {
      fprintf(
          stderr,
          "Usage: %s cave <filename> <birth limit> <death limit> <delay ms> "
          "<'steps' or 'auto'>\n",
          argv[0]);
      return 1;
    }
    initcave(argv);
  } else {
    printf("Unknown command: %s\n", argv[1]);
    return 1;
  }

  return 0;
}
