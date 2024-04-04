/********************************************************************************
** Form generated from reading UI file 'mainwindow2.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2_H
#define UI_MAINWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Graph
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_27;
    QPushButton *pushButton_28;
    QCustomPlot *widget;
    QLineEdit *lineEdit;
    QPushButton *pushButton_29;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Graph)
    {
        if (Graph->objectName().isEmpty())
            Graph->setObjectName("Graph");
        Graph->resize(700, 500);
        Graph->setMinimumSize(QSize(700, 500));
        Graph->setMaximumSize(QSize(700, 500));
        centralwidget = new QWidget(Graph);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 420, 100, 32));
        pushButton_27 = new QPushButton(centralwidget);
        pushButton_27->setObjectName("pushButton_27");
        pushButton_27->setGeometry(QRect(290, 420, 100, 32));
        pushButton_28 = new QPushButton(centralwidget);
        pushButton_28->setObjectName("pushButton_28");
        pushButton_28->setGeometry(QRect(390, 420, 100, 32));
        widget = new QCustomPlot(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 80, 681, 341));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 0, 321, 71));
        pushButton_29 = new QPushButton(centralwidget);
        pushButton_29->setObjectName("pushButton_29");
        pushButton_29->setGeometry(QRect(540, 0, 100, 32));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(380, 10, 61, 21));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(450, 10, 61, 21));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(380, 40, 61, 21));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(450, 40, 61, 21));
        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(540, 40, 61, 21));
        Graph->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Graph);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 700, 24));
        Graph->setMenuBar(menubar);
        statusbar = new QStatusBar(Graph);
        statusbar->setObjectName("statusbar");
        Graph->setStatusBar(statusbar);

        retranslateUi(Graph);

        QMetaObject::connectSlotsByName(Graph);
    } // setupUi

    void retranslateUi(QMainWindow *Graph)
    {
        Graph->setWindowTitle(QCoreApplication::translate("Graph", "Graph", nullptr));
        pushButton->setText(QCoreApplication::translate("Graph", "Calculator", nullptr));
        pushButton_27->setText(QCoreApplication::translate("Graph", "Credit", nullptr));
        pushButton_28->setText(QCoreApplication::translate("Graph", "Deposit", nullptr));
        lineEdit->setText(QCoreApplication::translate("Graph", "x^2-x-6", nullptr));
        pushButton_29->setText(QCoreApplication::translate("Graph", "Plot", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("Graph", "-10", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("Graph", "10", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("Graph", "-10", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("Graph", "10", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("Graph", "0.1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Graph: public Ui_Graph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2_H
