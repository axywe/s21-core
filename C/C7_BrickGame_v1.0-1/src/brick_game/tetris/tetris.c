#include "tetris.h"

static GameInfo_t gameInfo;
static BlockInfo_t blockInfo;

void initializeGame() {
  timeout(200);
  gameInfo.score = 0;
  gameInfo.high_score = readScore("score.txt");
  gameInfo.level = 1;
  gameInfo.speed = 100;
  gameInfo.pause = 0;
  srand(time(NULL));
  gameInfo.field = (int **)malloc(FIELD_HEIGHT * sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    gameInfo.field[i] = (int *)malloc(FIELD_WIDTH * sizeof(int));
    for (int j = 0; j < FIELD_WIDTH; j++) {
      gameInfo.field[i][j] = 0;
    }
  }
  blockInfo.nextBlockIndex = rand() % 7;
  spawnNewBlock();
}

void finalizeGame() {
  if (gameInfo.field != NULL) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      if (gameInfo.field[i] != NULL) {
        free(gameInfo.field[i]);
        gameInfo.field[i] = NULL;
      }
    }
  }
  if (gameInfo.field != NULL) {
    free(gameInfo.field);
    gameInfo.field = NULL;
  }
}

void spawnNewBlock() {
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
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      blockInfo.currentBlock[i][j] =
          tetrominoes[blockInfo.nextBlockIndex][i][j];
    }
  }
  blockInfo.currentX = FIELD_WIDTH / 2 - 2;
  blockInfo.currentY = 0;
  blockInfo.nextBlockIndex = rand() % 7;

  if (checkCollision(blockInfo.currentX, blockInfo.currentY)) {
    finalizeGame();
  }
}

bool checkCollision(int nx, int ny) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (blockInfo.currentBlock[y][x]) {
        int newX = nx + x;
        int newY = ny + y;
        if (newX < 0 || newX >= FIELD_WIDTH || newY >= FIELD_HEIGHT) {
          return true;
        }
        if (newY >= 0 && gameInfo.field[newY][newX] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}

void rotateBlock() {
  int tempBlock[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tempBlock[j][3 - i] = blockInfo.currentBlock[i][j];
    }
  }
  if (!checkCollision(blockInfo.currentX, blockInfo.currentY)) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        blockInfo.currentBlock[i][j] = tempBlock[i][j];
      }
    }
  }
}

void removeCompleteLines() {
  int linesCleared = 0;
  for (int y = FIELD_HEIGHT - 1; y >= 0; y--) {
    bool lineComplete = true;
    for (int x = 0; x < FIELD_WIDTH && lineComplete; x++) {
      if (gameInfo.field[y][x] == 0) {
        lineComplete = false;
      }
    }

    if (lineComplete) {
      for (int yy = y; yy > 0; yy--) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
          gameInfo.field[yy][x] = gameInfo.field[yy - 1][x];
        }
      }
      for (int x = 0; x < FIELD_WIDTH; x++) {
        gameInfo.field[0][x] = 0;
      }
      y++;
      linesCleared++;
    }
  }

  if (linesCleared > 0) {
    switch (linesCleared) {
      case 1:
        gameInfo.score += 100;
        break;
      case 2:
        gameInfo.score += 300;
        break;
      case 3:
        gameInfo.score += 700;
        break;
      case 4:
        gameInfo.score += 1500;
        break;
      default:
        break;
    }
    if (gameInfo.score >= gameInfo.level * 1000) {
      gameInfo.level++;
      if (gameInfo.level > 10) gameInfo.level = 10;
      gameInfo.speed = 1000 / gameInfo.level;
      timeout(gameInfo.speed);
    }
  }
}

void mergeBlockToField() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (blockInfo.currentBlock[y][x]) {
        int fieldX = blockInfo.currentX + x;
        int fieldY = blockInfo.currentY + y;
        if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
            fieldY < FIELD_HEIGHT) {
          gameInfo.field[fieldY][fieldX] = 1;
        }
      }
    }
  }
}

GameInfo_t updateCurrentState() {
  if (!gameInfo.pause && gameInfo.field != NULL) {
    if (checkCollision(blockInfo.currentX, blockInfo.currentY + 1)) {
      mergeBlockToField();
      removeCompleteLines();
      spawnNewBlock();
    } else {
      blockInfo.currentY++;
    }
  }
  return gameInfo;
}

BlockInfo_t getBlockInfo() { return blockInfo; }

void userInput(UserAction_t action, bool hold) {
  int nx = blockInfo.currentX, ny = blockInfo.currentY;
  switch (action) {
    case Left:
      nx--;
      break;
    case Right:
      nx++;
      break;
    case Down:
      if (hold) {
        ny += 2;
      } else {
        ny++;
      }
      break;
    case Action:
      rotateBlock();
      break;
    case Terminate:
      finalizeGame();
      break;
    case Pause:
      gameInfo.pause = !gameInfo.pause;
      break;
    default:
      break;
  }

  if (action == Down && hold) {
    bool flag = true;
    for (int fastDropY = blockInfo.currentY + 1; fastDropY <= ny && flag; fastDropY++) {
      if (checkCollision(blockInfo.currentX, fastDropY)) {
        ny = fastDropY - 1;
        flag = false;
      }
    }
  }

  if (action != Terminate && action != Pause) {
    if (!checkCollision(nx, ny)) {
      blockInfo.currentX = nx;
      blockInfo.currentY = ny;
    } else if (action == Down && hold) {
      mergeBlockToField();
      removeCompleteLines();
      spawnNewBlock();
    }
  }
}

int readScore(const char *filename) {
  int number = 0;
  FILE *file = fopen(filename, "r");
  if (file && fscanf(file, "%d", &number) == 1) {
    fclose(file);
  }
  return number;
}