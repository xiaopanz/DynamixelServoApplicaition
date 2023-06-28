#ifndef FIRSTLAYOUTSKINSLIPDELAYWINDOW_H
#define FIRSTLAYOUTSKINSLIPDELAYWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class FirstLayoutSkinSlipDelayWindow;
}

class FirstLayoutSkinSlipDelayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstLayoutSkinSlipDelayWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~FirstLayoutSkinSlipDelayWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_delaySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::FirstLayoutSkinSlipDelayWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
};

#endif // FIRSTLAYOUTSKINSLIPDELAYWINDOW_H
