#ifndef THIRDLAYOUTPUSHWINDOW_H
#define THIRDLAYOUTPUSHWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class ThirdLayoutPushWindow;
}

class ThirdLayoutPushWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThirdLayoutPushWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~ThirdLayoutPushWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::ThirdLayoutPushWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
    int firstReset = 1;
};

#endif // THIRDLAYOUTPUSHWINDOW_H
