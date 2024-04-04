#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int currentX, currentY;
  int currentBlock[4][4];
  int nextBlockIndex;
} BlockInfo_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);
void initializeGame(void);
void finalizeGame(void);
void displayField(const GameInfo_t *gameInfo);
bool checkCollision(int nx, int ny);
void spawnNewBlock();
void writeScore(int number, const char *filename);
int readScore(const char *filename);
bool gameOverText(GameInfo_t *gameInfo);
void removeCompleteLines();
BlockInfo_t getBlockInfo();
void mergeBlockToField();
void rotateBlock();

#endif  // TETRIS_H
