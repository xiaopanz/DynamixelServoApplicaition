#ifndef FIRSTLAYOUTCONTINUOUSSKINSLIPWINDOW_H
#define FIRSTLAYOUTCONTINUOUSSKINSLIPWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class FirstLayoutContinuousSkinSlipWindow;
}

class FirstLayoutContinuousSkinSlipWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstLayoutContinuousSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~FirstLayoutContinuousSkinSlipWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::FirstLayoutContinuousSkinSlipWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
};

#endif // FIRSTLAYOUTCONTINUOUSSKINSLIPWINDOW_H
