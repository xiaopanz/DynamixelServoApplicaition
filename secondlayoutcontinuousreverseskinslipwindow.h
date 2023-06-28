#ifndef SECONDLAYOUTCONTINUOUSREVERSESKINSLIPWINDOW_H
#define SECONDLAYOUTCONTINUOUSREVERSESKINSLIPWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class SecondLayoutContinuousReverseSkinSlipWindow;
}

class SecondLayoutContinuousReverseSkinSlipWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondLayoutContinuousReverseSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~SecondLayoutContinuousReverseSkinSlipWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::SecondLayoutContinuousReverseSkinSlipWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
};

#endif // SECONDLAYOUTCONTINUOUSREVERSESKINSLIPWINDOW_H
