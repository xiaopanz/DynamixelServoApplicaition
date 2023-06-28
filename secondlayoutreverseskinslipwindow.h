#ifndef SECONDLAYOUTREVERSESKINSLIPWINDOW_H
#define SECONDLAYOUTREVERSESKINSLIPWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class SecondLayoutReverseSkinSlipWindow;
}

class SecondLayoutReverseSkinSlipWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondLayoutReverseSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~SecondLayoutReverseSkinSlipWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::SecondLayoutReverseSkinSlipWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
};

#endif // SECONDLAYOUTREVERSESKINSLIPWINDOW_H
