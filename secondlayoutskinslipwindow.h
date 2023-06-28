#ifndef SECONDLAYOUTSKINSLIPWINDOW_H
#define SECONDLAYOUTSKINSLIPWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class SecondLayoutSkinSlipWindow;
}

class SecondLayoutSkinSlipWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondLayoutSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~SecondLayoutSkinSlipWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::SecondLayoutSkinSlipWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
    int firstReset = 1;
};

#endif // SECONDLAYOUTSKINSLIPWINDOW_H
