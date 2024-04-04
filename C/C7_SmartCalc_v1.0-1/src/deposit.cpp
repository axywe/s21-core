#include "deposit.h"

#include "credit.h"
#include "mainwindow.h"
#include "mainwindow2.h"
#include "ui_deposit.h"

deposit::deposit(QWidget* parent) : QMainWindow(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
  ui->tableWidgetDeposits->setColumnCount(2);
  ui->tableWidgetDeposits->setHorizontalHeaderLabels(QStringList() << "Month"
                                                                   << "Sum");

  ui->tableWidgetWithdraws->setColumnCount(2);
  ui->tableWidgetWithdraws->setHorizontalHeaderLabels(QStringList() << "Month"
                                                                    << "Sum");

  ui->tableWidgetDeposits->setEditTriggers(QAbstractItemView::DoubleClicked |
                                           QAbstractItemView::SelectedClicked);
  ui->tableWidgetWithdraws->setEditTriggers(QAbstractItemView::DoubleClicked |
                                            QAbstractItemView::SelectedClicked);
  ui->lineEdit_1->setPlaceholderText("Deposit amount");  // Введите сумму вклада
  ui->lineEdit_2->setPlaceholderText("Term in months");  // Срок в месяцах
  ui->lineEdit_3->setPlaceholderText(
      "Annual interest rate (%)");  // Годовая процентная ставка (%)
  ui->lineEdit_4->setPlaceholderText("Tax rate (%)");  // Налоговая ставка (%)
}

deposit::~deposit() { delete ui; }

void deposit::on_pushButton_28_clicked() {
  auto window = new credit(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void deposit::on_pushButton_clicked() {
  auto window = new MainWindow(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void deposit::on_pushButton_27_clicked() {
  auto window = new MainWindow2(this);
  window->setAttribute(Qt::WA_DeleteOnClose);
  window->show();
  this->hide();
}

void deposit::on_pushButton_2_clicked() {
  QVector<QPair<int, double>> deposits;
  QVector<QPair<int, double>> withdraws;

  for (int i = 0; i < ui->tableWidgetDeposits->rowCount(); ++i) {
    int month = ui->tableWidgetDeposits->item(i, 0)->text().toInt();
    double amount = ui->tableWidgetDeposits->item(i, 1)->text().toDouble();
    deposits.append(qMakePair(month, amount));
  }

  for (int i = 0; i < ui->tableWidgetWithdraws->rowCount(); ++i) {
    int month = ui->tableWidgetWithdraws->item(i, 0)->text().toInt();
    double amount = ui->tableWidgetWithdraws->item(i, 1)->text().toDouble();
    withdraws.append(qMakePair(month, amount));
  }
  double principalAmount = ui->lineEdit_1->text().toDouble();
  int termMonths = ui->lineEdit_2->text().toInt();
  double annualRate = ui->lineEdit_3->text().toDouble();
  double taxRate = ui->lineEdit_4->text().toDouble();

  bool capitalization = ui->checkBox_capitalization->isChecked();

  double totalAmount = principalAmount;
  double totalInterest = 0;
  double taxAmount = 0;

  // Применение операций пополнения и снятия
  for (int month = 1; month <= termMonths; ++month) {
    // Поиск и применение пополнений для текущего месяца
    for (const auto& deposit : deposits) {
      if (deposit.first == month) {
        totalAmount += deposit.second;
      }
    }

    // Поиск и применение снятий для текущего месяца
    for (const auto& withdraw : withdraws) {
      if (withdraw.first == month) {
        totalAmount -= withdraw.second;
      }
    }

    // Расчёт процентов для текущего месяца
    double interest = totalAmount * (annualRate / 12 / 100);
    if (capitalization) {
      totalAmount += interest;
    }
    totalInterest += interest;
  }

  // Расчёт налога и итоговой суммы
  taxAmount = totalInterest * (taxRate / 100);
  totalAmount -= taxAmount;

  // Отображение результатов
  ui->labelDepositResult->setText(
      QString("Total interest: %1\nTax amount: %2\nTotal amount: %3")
          .arg(totalInterest, 0, 'f', 2)
          .arg(taxAmount, 0, 'f', 2)
          .arg(totalAmount, 0, 'f', 2));
}

void deposit::on_pushButton_3_clicked() {
  int newRow = ui->tableWidgetDeposits->rowCount();
  ui->tableWidgetDeposits->insertRow(newRow);
  // Создание элементов QTableWidgetItem и установка их в таблицу
  ui->tableWidgetDeposits->setItem(
      newRow, 0, new QTableWidgetItem(""));  // Для даты/месяца
  ui->tableWidgetDeposits->setItem(newRow, 1,
                                   new QTableWidgetItem(""));  // Для суммы
  // Установка ячеек как редактируемых
  ui->tableWidgetDeposits->editItem(ui->tableWidgetDeposits->item(
      newRow, 0));  // Сразу открываем ячейку для редактирования
}

void deposit::on_pushButton_4_clicked() {
  int newRow = ui->tableWidgetWithdraws->rowCount();
  ui->tableWidgetWithdraws->insertRow(newRow);
  // Создание элементов QTableWidgetItem и установка их в таблицу
  ui->tableWidgetWithdraws->setItem(
      newRow, 0, new QTableWidgetItem(""));  // Для даты/месяца
  ui->tableWidgetWithdraws->setItem(newRow, 1,
                                    new QTableWidgetItem(""));  // Для суммы
  // Установка ячеек как редактируемых
  ui->tableWidgetWithdraws->editItem(ui->tableWidgetWithdraws->item(
      newRow, 0));  // Сразу открываем ячейку для редактирования
}
