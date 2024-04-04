#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QMainWindow>

namespace Ui {
class deposit;
}

class deposit : public QMainWindow {
  Q_OBJECT

 public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

 private slots:
  void on_pushButton_27_clicked();

  void on_pushButton_clicked();

  void on_pushButton_28_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

 private:
  Ui::deposit *ui;
};

#endif  // DEPOSIT_H
