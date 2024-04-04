#include "cave.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void load_cave(const char *filename, bool cave[MAX_ROWS][MAX_COLS], int *rows,
               int *cols) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%d %d", rows, cols);
  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {
      int cell;
      fscanf(file, "%d", &cell);
      cave[i][j] = cell;
    }
  }

  fclose(file);
}

void print_cave(bool cave[MAX_ROWS][MAX_COLS], int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%c", cave[i][j] ? '#' : ' ');
    }
    printf("\n");
  }
}

int count_alive_neighbors(bool cave[MAX_ROWS][MAX_COLS], int x, int y, int rows,
                          int cols) {
  int alive_neighbors = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int nx = x + i;
      int ny = y + j;
      if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
        alive_neighbors += cave[nx][ny];
      } else {
        alive_neighbors += 1;  // Cells outside the cave are considered alive
      }
    }
  }
  return alive_neighbors -
         cave[x][y];  // Subtract the cell itself if it's alive
}

void simulation_step(bool cave[MAX_ROWS][MAX_COLS],
                     bool newCave[MAX_ROWS][MAX_COLS], int rows, int cols,
                     int birthLimit, int deathLimit) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int alive_neighbors = count_alive_neighbors(cave, i, j, rows, cols);

      if (cave[i][j]) {
        newCave[i][j] = !(alive_neighbors < deathLimit);
      } else {
        newCave[i][j] = alive_neighbors > birthLimit;
      }
    }
  }
}

int initcave(char *argv[]) {
  int rows, cols;
  bool cave[MAX_ROWS][MAX_COLS];
  bool newCave[MAX_ROWS][MAX_COLS];

  load_cave(argv[2], cave, &rows, &cols);

  int birthLimit = atoi(argv[3]);
  int deathLimit = atoi(argv[4]);
  int delay = atoi(argv[5]);
  bool autoMode = strcmp(argv[6], "auto") == 0;

  while (true) {
    print_cave(cave, rows, cols);
    simulation_step(cave, newCave, rows, cols, birthLimit, deathLimit);

    if (memcmp(cave, newCave, sizeof(cave)) == 0) {
      printf("No changes in simulation, stopping.\n");
      break;
    }

    memcpy(cave, newCave, sizeof(cave));

    if (!autoMode) {
      printf("Press ENTER for the next step...\n");
      while (getchar() != '\n')
        ;
    } else {
      usleep(delay * 1000);
      system("clear");
    }
  }

  return EXIT_SUCCESS;
}
