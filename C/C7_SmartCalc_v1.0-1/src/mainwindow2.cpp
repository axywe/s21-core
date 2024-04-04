#include "mainwindow2.h"

#include "calculator.h"
#include "credit.h"
#include "deposit.h"
#include "mainwindow.h"
#include "ui_mainwindow2.h"

MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Graph) {
  ui->setupUi(this);

  ui->lineEdit_2->setPlaceholderText("X from");
  ui->lineEdit_3->setPlaceholderText("X to");
  ui->lineEdit_4->setPlaceholderText("Y from");
  ui->lineEdit_5->setPlaceholderText("Y to");
  ui->lineEdit_6->setPlaceholderText("Step");
}

MainWindow2::~MainWindow2() { delete ui; }

void MainWindow2::on_pushButton_clicked() {
  auto window = new MainWindow(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void MainWindow2::on_pushButton_27_clicked() {
  auto window = new credit(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void MainWindow2::on_pushButton_29_clicked() {
  const double defaultStepSize = 0.1;
  const double minStepSize = 0.001;

  double stepSize = ui->lineEdit_6->text().toDouble();
  if (stepSize < minStepSize) stepSize = defaultStepSize;

  // Получение диапазона осей из пользовательского интерфейса
  int xFrom = ui->lineEdit_2->text().toDouble();
  int xTo = ui->lineEdit_3->text().toDouble();
  int yFrom = ui->lineEdit_4->text().toDouble();
  int yTo = ui->lineEdit_5->text().toDouble();
  // qDebug()<<xFrom<<" " <<xTo<<" "<<yFrom<<" " << yTo;

  double xBegin = xFrom;
  double xEnd = xTo;
  ui->widget->xAxis->setRange(xFrom, xTo);
  ui->widget->yAxis->setRange(yFrom, yTo);

  QVector<double> x, y;

  for (double X = xBegin; X <= xEnd; X += stepSize) {
    QString input = text_formatter(ui->lineEdit->text().replace(
        "x", "(" + QString::number(X, 'f', 4) + ")"));
    QByteArray byteArray = input.toUtf8();

    char expr[MAX_EXPR_LENGTH];
    strncpy(expr, byteArray.constData(), MAX_EXPR_LENGTH - 1);
    expr[MAX_EXPR_LENGTH - 1] = '\0';
    char output[MAX_EXPR_LENGTH];
    infixToPostfix(expr, output);
    double result = calculatePostfix(output);
    // qDebug()<<input<<" "<<expr << " " <<output << " " << result;
    if (!(result == 1.0 / 0.0 || result == -1.0 / 0.0)) {
      x.push_back(X);
      y.push_back(result);
    }
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  // qDebug() << "X values:" << x;
  // qDebug() << "Y values:" << y;
  ui->widget->replot();
}

void MainWindow2::on_pushButton_28_clicked() {
  auto window = new deposit(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}
