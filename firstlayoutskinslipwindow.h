#ifndef FIRSTLAYOUTSKINSLIPWINDOW_H
#define FIRSTLAYOUTSKINSLIPWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

#include "servoutility.h"

namespace Ui {
class FirstLayoutSkinSlipWindow;
}

class FirstLayoutSkinSlipWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstLayoutSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~FirstLayoutSkinSlipWindow();

private slots:
    void on_angleSlider_valueChanged(int value);

    void on_velocitySlider_valueChanged(int value);

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::FirstLayoutSkinSlipWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
};

#endif // FIRSTLAYOUTSKINSLIPWINDOW_H
