#include "credit.h"

#include "deposit.h"
#include "mainwindow.h"
#include "mainwindow2.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) : QMainWindow(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  ui->lineEdit_2->setPlaceholderText("Total loan amount");
  ui->lineEdit_3->setPlaceholderText("Loan term (months)");
  ui->lineEdit_4->setPlaceholderText("Interest rate");
}

credit::~credit() { delete ui; }

void credit::on_pushButton_clicked() {
  auto window = new MainWindow(this);  // Создаем новое окно
  window->setAttribute(
      Qt::WA_DeleteOnClose);  // Указываем, чтобы окно удалилось после закрытия
  window->show();             // Показываем новое окно

  // Опционально, если вы хотите скрыть текущее окно:
  this->hide();
}

void credit::on_pushButton_27_clicked() {
  auto window = new MainWindow2(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void credit::on_pushButton_28_clicked() {
  auto window = new deposit(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void credit::on_pushButton_2_clicked() {
  double loanAmount = ui->lineEdit_2->text().toDouble();
  int term = ui->lineEdit_3->text().toInt();
  double interestRate = ui->lineEdit_4->text().toDouble() / 100 / 12;

  double monthlyPayment = 0;
  double totalPayment = 0;
  double overPayment = 0;

  if (ui->radioButton->isChecked()) {  // Аннуитетный кредит
    double annuityRatio = (interestRate * pow(1 + interestRate, term)) /
                          (pow(1 + interestRate, term) - 1);
    monthlyPayment = loanAmount * annuityRatio;
    totalPayment = monthlyPayment * term;
    overPayment = totalPayment - loanAmount;
  } else if (ui->radioButton_2->isChecked()) {  // Дифференцированный кредит
    double mainDebtPayment = loanAmount / term;
    for (int i = 0; i < term; ++i) {
      double interestPayment =
          (loanAmount - mainDebtPayment * i) * interestRate;
      monthlyPayment = mainDebtPayment + interestPayment;
      totalPayment += monthlyPayment;
    }
    overPayment = totalPayment - loanAmount;
  }

  QString result = QString(
                       "Monthly payment: %1 \nLoan overpayment: %2 "
                       "\nAdditional payment amount: %3")
                       .arg(QString::number(monthlyPayment, 'f', 2))
                       .arg(QString::number(overPayment, 'f', 2))
                       .arg(QString::number(totalPayment, 'f', 2));

  ui->label->setText(result);
}
