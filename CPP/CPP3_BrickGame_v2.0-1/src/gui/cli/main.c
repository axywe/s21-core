#include "../../brick_game/tetris/tetris.h"

int main() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_BLUE, COLOR_BLUE);
  keypad(stdscr, TRUE);
  initializeGame();

  while (getch() != ' ') {
    mvprintw(0, 0,
             "  _____ _____ _____ _____ _ _____\n |_   _|   __|_   _| __  | |  "
             " __|\n   | | |   __| | | |    -| |__   |\n   |_| |_____| |_| "
             "|__|__|_|_____|\n       Press 'space' to start\n  Arrows to "
             "move, space to action,\n     'p' to pause, 'q' to quit\n");
  }
  while (true) {
    int ch = getch();

    switch (ch) {
      case KEY_UP:
        userInput(Up, false);
        break;
      case KEY_DOWN:
        userInput(Down, true);
        break;
      case KEY_LEFT:
        userInput(Left, false);
        break;
      case KEY_RIGHT:
        userInput(Right, false);
        break;
      case 'q':
        userInput(Terminate, false);
        break;
      case 'p':
        userInput(Pause, false);
        break;
      case 's':
        userInput(Start, false);
        break;
      case ' ':
        userInput(Action, false);
        break;
      default:
        break;
    }

    GameInfo_t gameInfo = updateCurrentState();
    while (gameInfo.pause) {
      mvprintw(5, 20, "Paused. Press 'p' to continue");
      if (getch() == 'p') userInput(Pause, false);
      gameInfo = updateCurrentState();
    }
    if (gameInfo.field == NULL) {
      bool stop = gameOverText(&gameInfo);
      if (stop)
        break;
      else {
        initializeGame();
        continue;
      }
    }
    displayField(&gameInfo);
  }
  endwin();
  return 0;
}

void displayField(const GameInfo_t* gameInfo) {
  BlockInfo_t blockInfo = getBlockInfo();
  int tetrominoes[7][4][4] = {
      // I
      {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // T
      {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // O
      {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // S
      {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // Z
      {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // J
      {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      // L
      {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
  clear();
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      if (y >= blockInfo.currentY && y < blockInfo.currentY + 4 &&
          x >= blockInfo.currentX && x < blockInfo.currentX + 4 &&
          blockInfo
              .currentBlock[y - blockInfo.currentY][x - blockInfo.currentX]) {
        attron(COLOR_PAIR(1));
        mvprintw(y, x, "#");
      } else {
        mvprintw(y, x, "%c", gameInfo->field[y][x] ? '#' : '.');
      }
    }
  }
  mvprintw(0, 20, "Score %d", gameInfo->score);
  mvprintw(1, 20, "Level %d", gameInfo->level);
  mvprintw(2, 20, "High Score %d", gameInfo->high_score);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetrominoes[blockInfo.nextBlockIndex][i][j]) {
        mvprintw(2 + i, FIELD_WIDTH + 2 + j, "#");
      } else {
        mvprintw(2 + i, FIELD_WIDTH + 2 + j, " ");
      }
    }
  }
  refresh();
}

bool gameOverText(GameInfo_t* gameInfo) {
  mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 5, "GAME OVER");
  refresh();
  if (gameInfo->score > gameInfo->high_score) {
    writeScore(gameInfo->score, "score.txt");
  }
  mvprintw(10, 10, "Play again? (Y/N)");
  int stop = 0;
  while (stop == 0) {
    char choice = getch();
    if (choice == 'n' || choice == 'N') {
      stop = 1;
    } else if (choice == 'y' || choice == 'Y') {
      stop = 2;
    }
  }
  return stop == 1 ? true : false;
}

void writeScore(int number, const char* filename) {
  FILE* file = fopen(filename, "w+");
  if (file) {
    fprintf(file, "%d", number);
    fclose(file);
  }
}