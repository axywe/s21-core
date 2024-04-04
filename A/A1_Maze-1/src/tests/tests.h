#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../cave.h"
#include "../generator.h"
#include "../maze.h"
#include "../solver.h"

Suite *solver_suite(void);
Suite *maze_suite(void);
Suite *cave_suite(void);

#endif