#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include <QKeyEvent>
#include <QObject>
#include <QTimer>

class SnakeModel;
class SnakeView;

class SnakeController : public QObject {
  Q_OBJECT

 public:
  explicit SnakeController(SnakeModel *model, SnakeView *view);
  ~SnakeController() = default;

 protected:
  bool eventFilter(QObject *object, QEvent *event) override;

 private slots:
  void move();

 private:
  SnakeModel *model;
  SnakeView *view;
  QTimer timer;

  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
};

#endif  // SNAKECONTROLLER_H
