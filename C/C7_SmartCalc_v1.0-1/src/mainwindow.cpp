#include "mainwindow.h"

#include <iostream>

#include "./ui_mainwindow.h"
#include "calculator.h"
#include "credit.h"
#include "deposit.h"
#include "mainwindow2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

#include <QString>

QString text_formatter(QString input) {
  input.replace("asin", "d", Qt::CaseSensitive);
  input.replace("acos", "f", Qt::CaseSensitive);
  input.replace("atan", "g", Qt::CaseSensitive);
  input.replace("sin", "s", Qt::CaseSensitive);
  input.replace("cos", "c", Qt::CaseSensitive);
  input.replace("tan", "t", Qt::CaseSensitive);
  input.replace("ln", "n", Qt::CaseSensitive);
  input.replace("sqrt", "q", Qt::CaseSensitive);
  input.replace("log10", "l", Qt::CaseSensitive);

  return input;
}

void MainWindow::on_pushButton_1_clicked() {
  QString currentText = ui->label->text();

  currentText += '1';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_2_clicked() {
  QString currentText = ui->label->text();

  currentText += '2';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_3_clicked() {
  QString currentText = ui->label->text();

  currentText += '3';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_4_clicked() {
  QString currentText = ui->label->text();

  currentText += '4';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_5_clicked() {
  QString currentText = ui->label->text();

  currentText += '5';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_6_clicked() {
  QString currentText = ui->label->text();

  currentText += '6';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_7_clicked() {
  QString currentText = ui->label->text();

  currentText += '7';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_8_clicked() {
  QString currentText = ui->label->text();

  currentText += '8';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_9_clicked() {
  QString currentText = ui->label->text();

  currentText += '9';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_10_clicked() {
  QString currentText = ui->label->text();

  currentText += '0';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_11_clicked() {
  QString currentText = ui->label->text();

  currentText += '.';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_13_clicked() {
  QString currentText = ui->label->text();

  currentText += '+';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_14_clicked() {
  QString currentText = ui->label->text();

  currentText += '-';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_15_clicked() {
  QString currentText = ui->label->text();

  currentText += '*';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_16_clicked() {
  QString currentText = ui->label->text();

  currentText += '/';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_12_clicked() {
  QString currentText = text_formatter(ui->label->text());
  QByteArray byteArray = currentText.toUtf8();
  char expr[MAX_EXPR_LENGTH];
  strncpy(expr, byteArray.constData(), MAX_EXPR_LENGTH - 1);
  expr[MAX_EXPR_LENGTH - 1] = '\0';
  char output[MAX_EXPR_LENGTH];
  int status = SUCCESS;
  int res = infixToPostfix(expr, output);
  if (res != SUCCESS) {
    ui->label->setText("Error converting");
    status = FAILURE;
  }
  double result = calculatePostfix(output);
  qDebug() << currentText;
  // printf("expr: %s, res: %d, output: %s, result: %f\n", expr, res, output,
  // result); qDebug()<<currentText<<" "<<expr <<" res: " << res << " " <<output
  // << " " << result;
  if (status == SUCCESS) {
    if (result == -2000000001) {
      ui->label->setText("Error: Invalid expression\n");
    } else if (result == -2000000000) {
      ui->label->setText("Error: Division by zero\n");
    } else {
      ui->label->setText(QString::number(result));
    }
  }
}

void MainWindow::on_pushButton_17_clicked() {
  QString currentText = ui->label->text();

  currentText += '%';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_19_clicked() { ui->label->setText(""); }

void MainWindow::on_pushButton_26_clicked() {
  QString currentText = ui->label->text();

  currentText += '(';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_18_clicked() {
  QString currentText = ui->label->text();

  currentText += ')';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_32_clicked() {
  QString currentText = ui->label->text();

  currentText += "sin(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_22_clicked() {
  QString currentText = ui->label->text();

  currentText += "cos(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_23_clicked() {
  QString currentText = ui->label->text();

  currentText += "tan(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_35_clicked() {
  QString currentText = ui->label->text();

  currentText += "asin(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_24_clicked() {
  QString currentText = ui->label->text();

  currentText += "acos(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_21_clicked() {
  QString currentText = ui->label->text();

  currentText += "atan(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_34_clicked() {
  QString currentText = ui->label->text();

  currentText += "ln(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_25_clicked() {
  QString currentText = ui->label->text();

  currentText += "log10(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_20_clicked() {
  QString currentText = ui->label->text();

  currentText += "sqrt(";

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_31_clicked() {
  QString currentText = ui->label->text();

  currentText += '^';

  ui->label->setText(currentText);
}

void MainWindow::on_pushButton_clicked() {
  auto window = new MainWindow2(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void MainWindow::on_pushButton_27_clicked() {
  auto window = new credit(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void MainWindow::on_pushButton_28_clicked() {
  auto window = new deposit(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}
