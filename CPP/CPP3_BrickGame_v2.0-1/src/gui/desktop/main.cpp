// Название файла: main.cpp

#include <QApplication>

#include "../../brick_game/snake/snakecontroller.h"
#include "../../brick_game/snake/snakemodel.h"
#include "../../brick_game/snake/snakeview.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  SnakeModel model;
  SnakeView view(&model);
  SnakeController controller(&model, &view);

  view.show();

  return a.exec();
}
