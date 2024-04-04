#include "snakeview.h"

#include <QPainter>

#include "snakemodel.h"

SnakeView::SnakeView(SnakeModel *model, QWidget *parent)
    : QWidget(parent), model(model) {
  setFixedSize(400, 600);
}

void SnakeView::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  QPainter qp(this);
  const int sidePanelWidth = 100;
  const int gameAreaWidth = width() - sidePanelWidth;

  qp.setBrush(Qt::red);
  qp.drawRect(model->getApple().x() * 30, model->getApple().y() * 30, 30, 30);

  qp.setBrush(Qt::green);
  for (const auto &part : model->getSnake()) {
    qp.drawRect(part.x() * 30, part.y() * 30, 30, 30);
  }

  qp.setBrush(QColor(240, 240, 240));
  qp.drawRect(gameAreaWidth, 0, sidePanelWidth, height());

  qp.setPen(Qt::black);
  qp.setFont(QFont("Arial", 16));
  qp.drawText(gameAreaWidth + 5, 30,
              "Score: " + QString::number(model->getScore()));
  qp.drawText(gameAreaWidth + 5, 50,
              "Level: " + QString::number(model->getLevel()));
  qp.drawText(gameAreaWidth + 5, 70,
              "Max score:\n" + QString::number(model->getMaxScore()));
  if (model->isGamePaused()) {
    qp.drawText(gameAreaWidth + 20, 300, "PAUSED");
  } else if (model->isGameWon()) {
    qp.drawText(gameAreaWidth, 300, "YOU WIN!");
  } else if (model->isGameOver()) {
    qp.drawText(gameAreaWidth, 300, "GAME OVER");
  }
}
