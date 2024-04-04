#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <QWidget>

class SnakeModel;

class SnakeView : public QWidget {
  Q_OBJECT

 public:
  explicit SnakeView(SnakeModel *model, QWidget *parent = nullptr);
  ~SnakeView() override = default;

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  SnakeModel *model;
};

#endif  // SNAKEVIEW_H
