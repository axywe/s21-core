#include "snakemodel.h"

#include <QFile>
#include <QRandomGenerator>
#include <QTextStream>
#include <algorithm>

SnakeModel::SnakeModel()
    : direction(Right),
      gameOver(false),
      gameWon(false),
      gamePaused(false),
      score(0),
      level(1) {
  initGame();
}

void SnakeModel::initGame() {
  snake.clear();
  for (int i = 0; i < 4; ++i) {
    snake.emplace_back(5 - i, 10);
  }
  direction = Right;
  gameOver = false;
  gameWon = false;
  gamePaused = false;
  score = 0;
  level = 1;
  placeApple();
  readMaxScore();
}

void SnakeModel::move(Direction dir) {
  if (gameOver || gamePaused || gameWon) return;
  QPoint head = snake.front();

  switch (dir) {
    case Left:
      head.rx() -= 1;
      break;
    case Right:
      head.rx() += 1;
      break;
    case Up:
      head.ry() -= 1;
      break;
    case Down:
      head.ry() += 1;
      break;
  }

  snake.insert(snake.begin(), head);
  if (head != apple) {
    snake.pop_back();
  } else {
    placeApple();
    updateScore(10);
  }
}

bool SnakeModel::checkCollision() {
  QPoint head = snake.front();
  if (head.x() < 0 || head.x() >= 10 || head.y() < 0 || head.y() >= 20 ||
      std::find(snake.begin() + 1, snake.end(), head) != snake.end()) {
    gameOver = true;
    writeMaxScore();
    return true;
  }
  if (score == 200) {
    gameWon = true;
    writeMaxScore();
    return true;
  }
  return false;
}

void SnakeModel::placeApple() {
  int x, y;
  do {
    x = QRandomGenerator::global()->bounded(10);
    y = QRandomGenerator::global()->bounded(20);
  } while (std::find(snake.begin(), snake.end(), QPoint(x, y)) != snake.end());
  apple.setX(x);
  apple.setY(y);
}

bool SnakeModel::isGameOver() const { return gameOver; }

bool SnakeModel::isGameWon() const { return gameWon; }

bool SnakeModel::isGamePaused() const { return gamePaused; }

void SnakeModel::togglePause() { gamePaused = !gamePaused; }

void SnakeModel::setGameOver(bool over) { gameOver = over; }

void SnakeModel::setGameWon(bool won) { gameWon = won; }

int SnakeModel::getScore() const { return score; }

int SnakeModel::getLevel() const { return level; }

int SnakeModel::getMaxScore() const { return max_score; }

const std::vector<QPoint>& SnakeModel::getSnake() const { return snake; }

const QPoint& SnakeModel::getApple() const { return apple; }

SnakeModel::Direction SnakeModel::getDirection() const { return direction; }

void SnakeModel::setDirection(Direction dir) { direction = dir; }

void SnakeModel::updateScore(int points) {
  score += points;
  level = (score + 1) / 10;
  if (level > 10) level = 10;
  if (score >= 200) gameWon = true;
}

void SnakeModel::readMaxScore() {
  QFile file("snake_max.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    max_score = 0;
    return;
  }

  QTextStream in(&file);
  QString line = in.readLine();
  max_score = line.toInt();
  file.close();
}

void SnakeModel::writeMaxScore() {
  if (score > max_score) {
    QFile file("snake_max.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << score;
      max_score = score;
      file.close();
    }
  }
}
