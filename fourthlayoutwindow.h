#ifndef FOURTHLAYOUTWINDOW_H
#define FOURTHLAYOUTWINDOW_H

#include "fourthlayoutonewindow.h"
#include "servoutility.h"
#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>

class FourthLayoutOneWindow;

namespace Ui {
class FourthLayoutWindow;
}

class FourthLayoutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FourthLayoutWindow(QWidget *parent = 0);
    ~FourthLayoutWindow();
    ServoUtility servoUtility;

private slots:
    void on_goBackButton_clicked();

    void on_skinSlipButton_clicked();

    void on_continuousSkinSlipButton_clicked();

    void on_oneButton_clicked();

    void on_fourButton_clicked();

private:
    Ui::FourthLayoutWindow *ui;
    QWidget* parent;
    FourthLayoutOneWindow *fourthLayoutOneWindow;
    int dxl_ids_4[NUM_OF_DXL_4] = { DXL5_ID, DXL9_ID, DXL7_ID, DXL8_ID, DXL6_ID, DXL10_ID };
};

#endif // FOURTHLAYOUTWINDOW_H
