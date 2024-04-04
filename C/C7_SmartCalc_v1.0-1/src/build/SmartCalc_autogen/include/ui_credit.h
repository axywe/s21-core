/********************************************************************************
** Form generated from reading UI file 'credit.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDIT_H
#define UI_CREDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_credit
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_28;
    QPushButton *pushButton;
    QPushButton *pushButton_27;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *credit)
    {
        if (credit->objectName().isEmpty())
            credit->setObjectName("credit");
        credit->resize(700, 500);
        credit->setMinimumSize(QSize(700, 500));
        credit->setMaximumSize(QSize(700, 500));
        centralwidget = new QWidget(credit);
        centralwidget->setObjectName("centralwidget");
        pushButton_28 = new QPushButton(centralwidget);
        pushButton_28->setObjectName("pushButton_28");
        pushButton_28->setGeometry(QRect(390, 420, 100, 32));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 420, 100, 32));
        pushButton_27 = new QPushButton(centralwidget);
        pushButton_27->setObjectName("pushButton_27");
        pushButton_27->setGeometry(QRect(290, 420, 100, 32));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(220, 10, 281, 41));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(220, 60, 281, 41));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(220, 110, 281, 41));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 210, 681, 211));
        label->setStyleSheet(QString::fromUtf8("border-radius: 30px; /* \320\227\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\270\320\265 \321\203\320\263\320\273\320\276\320\262 */\n"
"background-color: #333333; /* \320\221\320\265\320\273\321\213\320\271 \321\204\320\276\320\275\320\276\320\262\321\213\320\271 \321\206\320\262\320\265\321\202 \320\264\320\273\321\217 \320\272\320\275\320\276\320\277\320\272\320\270 */\n"
"color: white; /* \320\246\320\262\320\265\321\202 \321\202\320\265\320\272\321\201\321\202\320\260 */\n"
"font-size: 28px; /* \320\240\320\260\320\267\320\274\320\265\321\200 \321\210\321\200\320\270\321\204\321\202\320\260 */\n"
"padding: 5px; /* \320\236\321\202\321\201\321\202\321\203\320\277\321\213 \320\262\320\276\320\272\321\200\321\203\320\263 \321\202\320\265\320\272\321\201\321\202\320\260 \320\262\320\275\321\203\321\202\321\200\320\270 \320\272\320\275\320\276\320\277\320\272\320\270 */\n"
"border: 1px solid #cccccc; /* \320\242\320\276\320\275\320\272\320\260\321\217 \320\263\321\200\320\260\320\275\320"
                        "\270\321\206\320\260 \320\262\320\276\320\272\321\200\321\203\320\263 \320\272\320\275\320\276\320\277\320\272\320\270 */"));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(230, 160, 111, 20));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(340, 160, 161, 20));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(310, 180, 100, 32));
        credit->setCentralWidget(centralwidget);
        menubar = new QMenuBar(credit);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 700, 24));
        credit->setMenuBar(menubar);
        statusbar = new QStatusBar(credit);
        statusbar->setObjectName("statusbar");
        credit->setStatusBar(statusbar);

        retranslateUi(credit);

        QMetaObject::connectSlotsByName(credit);
    } // setupUi

    void retranslateUi(QMainWindow *credit)
    {
        credit->setWindowTitle(QCoreApplication::translate("credit", "MainWindow", nullptr));
        pushButton_28->setText(QCoreApplication::translate("credit", "Deposit", nullptr));
        pushButton->setText(QCoreApplication::translate("credit", "Calculator", nullptr));
        pushButton_27->setText(QCoreApplication::translate("credit", "Graph", nullptr));
        lineEdit_2->setText(QString());
        lineEdit_3->setText(QString());
        lineEdit_4->setText(QString());
        label->setText(QString());
        radioButton->setText(QCoreApplication::translate("credit", "Annuity", nullptr));
        radioButton_2->setText(QCoreApplication::translate("credit", "Differentiable", nullptr));
        pushButton_2->setText(QCoreApplication::translate("credit", "Calculate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class credit: public Ui_credit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDIT_H
