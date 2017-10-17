/********************************************************************************
** Form generated from reading UI file 'FishHunterRecorder.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FISHHUNTERRECORDER_H
#define UI_FISHHUNTERRECORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FishHunterRecorderClass
{
public:
    QWidget *centralWidget;
    QLabel *GameView;
    QLabel *DebugMessage;

    void setupUi(QMainWindow *FishHunterRecorderClass)
    {
        if (FishHunterRecorderClass->objectName().isEmpty())
            FishHunterRecorderClass->setObjectName(QStringLiteral("FishHunterRecorderClass"));
        FishHunterRecorderClass->resize(1000, 600);
        centralWidget = new QWidget(FishHunterRecorderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GameView = new QLabel(centralWidget);
        GameView->setObjectName(QStringLiteral("GameView"));
        GameView->setGeometry(QRect(0, 0, 900, 600));
        DebugMessage = new QLabel(centralWidget);
        DebugMessage->setObjectName(QStringLiteral("DebugMessage"));
        DebugMessage->setGeometry(QRect(900, 50, 100, 550));
        FishHunterRecorderClass->setCentralWidget(centralWidget);

        retranslateUi(FishHunterRecorderClass);

        QMetaObject::connectSlotsByName(FishHunterRecorderClass);
    } // setupUi

    void retranslateUi(QMainWindow *FishHunterRecorderClass)
    {
        FishHunterRecorderClass->setWindowTitle(QApplication::translate("FishHunterRecorderClass", "FishHunterRecorder", Q_NULLPTR));
        GameView->setText(QApplication::translate("FishHunterRecorderClass", "TextLabel", Q_NULLPTR));
        DebugMessage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FishHunterRecorderClass: public Ui_FishHunterRecorderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FISHHUNTERRECORDER_H
