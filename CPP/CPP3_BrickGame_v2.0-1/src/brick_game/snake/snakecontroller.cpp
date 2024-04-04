#include "snakecontroller.h"

#include <QKeyEvent>

#include "snakemodel.h"
#include "snakeview.h"

SnakeController::SnakeController(SnakeModel *model, SnakeView *view)
    : QObject(view), model(model), view(view) {
  view->installEventFilter(this);
  connect(&timer, &QTimer::timeout, this, &SnakeController::move);
  timer.start(500);
}

bool SnakeController::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    keyPressEvent(static_cast<QKeyEvent *>(event));
    return true;
  } else if (event->type() == QEvent::KeyRelease) {
    keyReleaseEvent(static_cast<QKeyEvent *>(event));
    return true;
  }
  return QObject::eventFilter(object, event);
}

void SnakeController::move() {
  model->move(model->getDirection());
  if (model->checkCollision()) {
    timer.stop();
  }
  view->update();
}

void SnakeController::keyPressEvent(QKeyEvent *event) {
  if ((model->isGameOver() && event->key() == Qt::Key_R) ||
      (model->isGameWon() && event->key() == Qt::Key_R)) {
    model->initGame();
    timer.start(1000 / model->getLevel());
    view->update();
  }
  if (event->key() == Qt::Key_P) {
    model->togglePause();
    if (model->isGamePaused()) {
      timer.stop();
    } else {
      timer.start(1000 / model->getLevel());
    }
    view->update();
    return;
  }
  if (event->key() == Qt::Key_Space) {
    timer.start(50);
    return;
  }
  if (model->isGamePaused()) return;
  int key = event->key();
  SnakeModel::Direction dir = model->getDirection();
  if (key == Qt::Key_Left && dir != SnakeModel::Right) {
    model->setDirection(SnakeModel::Left);
  } else if (key == Qt::Key_Right && dir != SnakeModel::Left) {
    model->setDirection(SnakeModel::Right);
  } else if (key == Qt::Key_Up && dir != SnakeModel::Down) {
    model->setDirection(SnakeModel::Up);
  } else if (key == Qt::Key_Down && dir != SnakeModel::Up) {
    model->setDirection(SnakeModel::Down);
  }
}

void SnakeController::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    timer.start(1000 / model->getLevel());
  }
}
