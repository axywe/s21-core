#include <gtest/gtest.h>

#include <QTemporaryFile>

#include "../brick_game/snake/snakemodel.h"

class SnakeModelTest : public ::testing::Test {
 protected:
  void SetUp() override {
    QTemporaryFile tempFile;
    ASSERT_TRUE(tempFile.open());
    maxScoreFileName = tempFile.fileName();
    tempFile.close();

    model = new SnakeModel;
  }

  void TearDown() override { delete model; }

  QString maxScoreFileName;
  SnakeModel *model;
};

TEST_F(SnakeModelTest, InitialConditions) {
  EXPECT_FALSE(model->isGameOver());
  EXPECT_FALSE(model->isGameWon());
  EXPECT_FALSE(model->isGamePaused());
  EXPECT_EQ(model->getDirection(), SnakeModel::Right);
  EXPECT_EQ(model->getScore(), 0);

  auto snake = model->getSnake();
  EXPECT_EQ(snake.size(), 4);
}

TEST_F(SnakeModelTest, MoveWithoutCollision) {
  model->move(SnakeModel::Right);
  EXPECT_FALSE(model->isGameOver());
  EXPECT_FALSE(model->isGameWon());
  auto snake = model->getSnake();
  EXPECT_EQ(snake.front().x() - snake[1].x(), 1);
}

TEST_F(SnakeModelTest, CollisionWithWall) {
  // Move the snake to collide with the wall
  for (int i = 0; i < 5; ++i) {
    model->move(SnakeModel::Right);
  }
  ASSERT_TRUE(model->checkCollision());
  EXPECT_TRUE(model->isGameOver());
}

TEST_F(SnakeModelTest, EatApple) {
  // Set the apple position to simulate the snake eating an apple
  QPoint currentHead = model->getSnake().front();
  model->placeApple();
  *const_cast<QPoint *>(&model->getApple()) =
      QPoint(currentHead.x() + 1, currentHead.y());
  model->move(SnakeModel::Right);
  EXPECT_EQ(model->getScore(), 10);
  EXPECT_EQ(model->getLevel(), 1);
}

TEST_F(SnakeModelTest, TogglePause) {
  model->togglePause();
  EXPECT_TRUE(model->isGamePaused());

  model->togglePause();
  EXPECT_FALSE(model->isGamePaused());
}

GTEST_API_ int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}