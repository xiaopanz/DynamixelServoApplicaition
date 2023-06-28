#ifndef SECONDLAYOUTCONTINUOUSSKINSLIPWINDOW_H
#define SECONDLAYOUTCONTINUOUSSKINSLIPWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class SecondLayoutContinuousSkinSlipWindow;
}

class SecondLayoutContinuousSkinSlipWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondLayoutContinuousSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~SecondLayoutContinuousSkinSlipWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::SecondLayoutContinuousSkinSlipWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
    int firstReset = 1;
};

#endif // SECONDLAYOUTCONTINUOUSSKINSLIPWINDOW_H
