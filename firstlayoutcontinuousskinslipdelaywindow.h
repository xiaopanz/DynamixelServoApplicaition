#ifndef FIRSTLAYOUTCONTINUOUSSKINSLIPDELAYWINDOW_H
#define FIRSTLAYOUTCONTINUOUSSKINSLIPDELAYWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class FirstLayoutContinuousSkinSlipDelayWindow;
}

class FirstLayoutContinuousSkinSlipDelayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstLayoutContinuousSkinSlipDelayWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~FirstLayoutContinuousSkinSlipDelayWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_delaySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::FirstLayoutContinuousSkinSlipDelayWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
};

#endif // FIRSTLAYOUTCONTINUOUSSKINSLIPDELAYWINDOW_H
