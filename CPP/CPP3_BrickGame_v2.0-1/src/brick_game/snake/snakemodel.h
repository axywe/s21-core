#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <QPoint>
#include <vector>

class SnakeModel {
 public:
  enum Direction { Left, Right, Up, Down };

  SnakeModel();
  ~SnakeModel() = default;

  void initGame();
  void move(Direction dir);
  void placeApple();
  bool checkCollision();
  bool isGameOver() const;
  bool isGameWon() const;
  bool isGamePaused() const;
  void togglePause();
  void setGameOver(bool over);
  void setGameWon(bool won);
  int getScore() const;
  int getLevel() const;
  int getMaxScore() const;
  void updateScore(int points);
  const std::vector<QPoint>& getSnake() const;
  const QPoint& getApple() const;
  Direction getDirection() const;
  void setDirection(Direction dir);
  void readMaxScore();
  void writeMaxScore();

 private:
  std::vector<QPoint> snake;
  QPoint apple;
  Direction direction;
  bool gameOver;
  bool gameWon;
  bool gamePaused;
  int score;
  int level;
  int max_score;
};

#endif  // SNAKEMODEL_H
