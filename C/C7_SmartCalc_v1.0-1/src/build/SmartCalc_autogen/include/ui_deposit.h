/********************************************************************************
** Form generated from reading UI file 'deposit.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOSIT_H
#define UI_DEPOSIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deposit
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_27;
    QPushButton *pushButton_28;
    QLabel *labelDepositResult;
    QLineEdit *lineEdit_1;
    QCheckBox *checkBox_capitalization;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QTableWidget *tableWidgetDeposits;
    QTableWidget *tableWidgetWithdraws;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *deposit)
    {
        if (deposit->objectName().isEmpty())
            deposit->setObjectName("deposit");
        deposit->resize(700, 500);
        deposit->setMinimumSize(QSize(700, 500));
        deposit->setMaximumSize(QSize(700, 500));
        centralwidget = new QWidget(deposit);
        centralwidget->setObjectName("centralwidget");
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(310, 180, 100, 32));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 420, 100, 32));
        pushButton_27 = new QPushButton(centralwidget);
        pushButton_27->setObjectName("pushButton_27");
        pushButton_27->setGeometry(QRect(290, 420, 100, 32));
        pushButton_28 = new QPushButton(centralwidget);
        pushButton_28->setObjectName("pushButton_28");
        pushButton_28->setGeometry(QRect(390, 420, 100, 32));
        labelDepositResult = new QLabel(centralwidget);
        labelDepositResult->setObjectName("labelDepositResult");
        labelDepositResult->setGeometry(QRect(10, 210, 681, 211));
        labelDepositResult->setStyleSheet(QString::fromUtf8("border-radius: 30px; /* \320\227\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\270\320\265 \321\203\320\263\320\273\320\276\320\262 */\n"
"background-color: #333333; /* \320\221\320\265\320\273\321\213\320\271 \321\204\320\276\320\275\320\276\320\262\321\213\320\271 \321\206\320\262\320\265\321\202 \320\264\320\273\321\217 \320\272\320\275\320\276\320\277\320\272\320\270 */\n"
"color: white; /* \320\246\320\262\320\265\321\202 \321\202\320\265\320\272\321\201\321\202\320\260 */\n"
"font-size: 28px; /* \320\240\320\260\320\267\320\274\320\265\321\200 \321\210\321\200\320\270\321\204\321\202\320\260 */\n"
"padding: 5px; /* \320\236\321\202\321\201\321\202\321\203\320\277\321\213 \320\262\320\276\320\272\321\200\321\203\320\263 \321\202\320\265\320\272\321\201\321\202\320\260 \320\262\320\275\321\203\321\202\321\200\320\270 \320\272\320\275\320\276\320\277\320\272\320\270 */\n"
"border: 1px solid #cccccc; /* \320\242\320\276\320\275\320\272\320\260\321\217 \320\263\321\200\320\260\320\275\320"
                        "\270\321\206\320\260 \320\262\320\276\320\272\321\200\321\203\320\263 \320\272\320\275\320\276\320\277\320\272\320\270 */"));
        lineEdit_1 = new QLineEdit(centralwidget);
        lineEdit_1->setObjectName("lineEdit_1");
        lineEdit_1->setGeometry(QRect(200, 0, 281, 41));
        checkBox_capitalization = new QCheckBox(centralwidget);
        checkBox_capitalization->setObjectName("checkBox_capitalization");
        checkBox_capitalization->setGeometry(QRect(310, 160, 111, 20));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(200, 40, 281, 41));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(200, 80, 281, 41));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(200, 120, 281, 41));
        tableWidgetDeposits = new QTableWidget(centralwidget);
        tableWidgetDeposits->setObjectName("tableWidgetDeposits");
        tableWidgetDeposits->setGeometry(QRect(0, 0, 191, 161));
        tableWidgetWithdraws = new QTableWidget(centralwidget);
        tableWidgetWithdraws->setObjectName("tableWidgetWithdraws");
        tableWidgetWithdraws->setGeometry(QRect(490, 0, 201, 161));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(40, 180, 100, 32));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(540, 180, 100, 32));
        deposit->setCentralWidget(centralwidget);
        menubar = new QMenuBar(deposit);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 700, 24));
        deposit->setMenuBar(menubar);
        statusbar = new QStatusBar(deposit);
        statusbar->setObjectName("statusbar");
        deposit->setStatusBar(statusbar);

        retranslateUi(deposit);

        QMetaObject::connectSlotsByName(deposit);
    } // setupUi

    void retranslateUi(QMainWindow *deposit)
    {
        deposit->setWindowTitle(QCoreApplication::translate("deposit", "MainWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("deposit", "Calculate", nullptr));
        pushButton->setText(QCoreApplication::translate("deposit", "Calculator", nullptr));
        pushButton_27->setText(QCoreApplication::translate("deposit", "Graph", nullptr));
        pushButton_28->setText(QCoreApplication::translate("deposit", "Credit", nullptr));
        labelDepositResult->setText(QString());
        lineEdit_1->setText(QString());
        checkBox_capitalization->setText(QCoreApplication::translate("deposit", "Capitalization", nullptr));
        lineEdit_2->setText(QString());
        lineEdit_3->setText(QString());
        lineEdit_4->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("deposit", "Add deposit", nullptr));
        pushButton_4->setText(QCoreApplication::translate("deposit", "Add withdraw", nullptr));
    } // retranslateUi

};

namespace Ui {
    class deposit: public Ui_deposit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOSIT_H
