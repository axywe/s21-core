#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QVector>
namespace Ui {
class Graph;
}

class MainWindow2 : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow2(QWidget *parent = nullptr);
  ~MainWindow2();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_29_clicked();

  void on_pushButton_27_clicked();

  void on_pushButton_28_clicked();

 private:
  Ui::Graph *ui;
};

#endif  // MAINWINDOW2_H
