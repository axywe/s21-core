#ifndef CAVE_H
#define CAVE_H

#define MAX_ROWS 50
#define MAX_COLS 50

#include <stdbool.h>

void load_cave(const char *filename, bool cave[MAX_ROWS][MAX_COLS], int *rows,
               int *cols);
void print_cave(bool cave[MAX_ROWS][MAX_COLS], int rows, int cols);
int count_alive_neighbors(bool cave[MAX_ROWS][MAX_COLS], int x, int y, int rows,
                          int cols);
void simulation_step(bool cave[MAX_ROWS][MAX_COLS],
                     bool newCave[MAX_ROWS][MAX_COLS], int rows, int cols,
                     int birthLimit, int deathLimit);
int initcave(char *argv[]);

#endif