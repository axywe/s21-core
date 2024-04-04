#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 10
#define WIDTH 10
#define EPISODES 10000
#define LEARNING_RATE 0.1
#define DISCOUNT_FACTOR 0.95
#define RANDOM_MOVE_PROBABILITY 0.1

enum { UP, DOWN, LEFT, RIGHT, ACTION_COUNT };

int rewards[HEIGHT][WIDTH];
double q_values[HEIGHT][WIDTH][ACTION_COUNT];
int goal_x = 9;
int goal_y = 9;

int is_terminal_state(int x, int y) { return x == goal_x && y == goal_y; }

void initialize_rewards() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      rewards[i][j] = -1;
    }
  }
  rewards[goal_x][goal_y] = 100;
}

void initialize_q_values() {
  for (int x = 0; x < HEIGHT; x++) {
    for (int y = 0; y < WIDTH; y++) {
      for (int a = 0; a < ACTION_COUNT; a++) {
        q_values[x][y][a] = 0.0;
      }
    }
  }
}

void take_action(int *x, int *y, int action) {
  switch (action) {
    case UP:
      if (*x > 0) (*x)--;
      break;
    case DOWN:
      if (*x < HEIGHT - 1) (*x)++;
      break;
    case LEFT:
      if (*y > 0) (*y)--;
      break;
    case RIGHT:
      if (*y < WIDTH - 1) (*y)++;
      break;
  }
}

int choose_action(int x, int y) {
  // Explore with a probability of RANDOM_MOVE_PROBABILITY
  if ((double)rand() / RAND_MAX < RANDOM_MOVE_PROBABILITY) {
    return rand() % ACTION_COUNT;
  }

  // Exploit (choose best action)
  double max_value = -1e9;
  int action = 0;
  for (int a = 0; a < ACTION_COUNT; a++) {
    if (q_values[x][y][a] > max_value) {
      max_value = q_values[x][y][a];
      action = a;
    }
  }
  return action;
}

void update_q_values() {
  for (int episode = 0; episode < EPISODES; episode++) {
    int x = rand() % HEIGHT;
    int y = rand() % WIDTH;

    while (!is_terminal_state(x, y)) {
      int action = choose_action(x, y);
      int old_x = x, old_y = y;
      take_action(&x, &y, action);

      // Update Q-value using Bellman equation
      double max_future_q = -1e9;
      for (int a = 0; a < ACTION_COUNT; a++) {
        if (q_values[x][y][a] > max_future_q) {
          max_future_q = q_values[x][y][a];
        }
      }

      double reward = rewards[x][y];
      q_values[old_x][old_y][action] +=
          LEARNING_RATE * (reward + DISCOUNT_FACTOR * max_future_q -
                           q_values[old_x][old_y][action]);
    }
  }
}

void print_optimal_path(int start_x, int start_y) {
  if (start_x == goal_x && start_y == goal_y) {
    printf("Goal reached!\n");
    return;
  }

  printf("Path from (%d, %d) to Goal (%d, %d): ", start_x, start_y, goal_x,
         goal_y);

  while (!is_terminal_state(start_x, start_y)) {
    int action = choose_action(start_x, start_y);
    printf("(%d, %d) -> ", start_x, start_y);
    take_action(&start_x, &start_y, action);
  }

  printf("(%d, %d) Goal\n", start_x, start_y);
}

// int main() {
//     srand(time(NULL));
//     initialize_rewards();
//     initialize_q_values();
//     update_q_values();

//     int start_x = 0; // Starting point
//     int start_y = 0;

//     print_optimal_path(start_x, start_y);

//     return 0;
// }
