#ifndef SECONDLAYOUTWINDOW_H
#define SECONDLAYOUTWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include "secondlayoutskinslipwindow.h"
#include "secondlayoutreverseskinslipwindow.h"
#include "secondlayoutcontinuousskinslipwindow.h"
#include "secondlayoutcontinuousreverseskinslipwindow.h"
#include "servoutility.h"

class SecondLayoutSkinSlipWindow;
class SecondLayoutReverseSkinSlipWindow;
class SecondLayoutContinuousSkinSlipWindow;
class SecondLayoutContinuousReverseSkinSlipWindow;

namespace Ui {
class SecondLayoutWindow;
}

class SecondLayoutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondLayoutWindow(QWidget *parent = 0);
    ~SecondLayoutWindow();
    ServoUtility servoUtility;
    int dxl_ids_2[NUM_OF_DXL_2] = { DXL5_ID, DXL6_ID, DXL7_ID, DXL8_ID, DXL9_ID, DXL10_ID };

private slots:
    void on_goBackButton_clicked();

    void on_skinSlipButton_clicked();

    void on_reverseSkinSlipButton_clicked();

    void on_continuousSkinSlipButton_clicked();

    void on_continuousReverseSkinSlipButton_clicked();

private:
    Ui::SecondLayoutWindow *ui;
    QWidget* parent;
    SecondLayoutSkinSlipWindow *secondLayoutSkinSlipWindow;
    SecondLayoutReverseSkinSlipWindow *secondLayoutReverseSkinSlipWindow;
    SecondLayoutContinuousSkinSlipWindow *secondLayoutContinuousSkinSlipWindow;
    SecondLayoutContinuousReverseSkinSlipWindow *secondLayoutContinuousReverseSkinSlipWindow;
};

#endif // SECONDLAYOUTWINDOW_H
