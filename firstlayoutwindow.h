#ifndef FIRSTLAYOUTWINDOW_H
#define FIRSTLAYOUTWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include "firstlayoutskinslipwindow.h"
#include "firstlayoutskinslipdelaywindow.h"
#include "firstlayoutsqueezewindow.h"
#include "firstlayoutpushwindow.h"
#include "firstlayoutcontinuousskinslipwindow.h"
#include "firstlayoutcontinuousskinslipdelaywindow.h"
#include "servoutility.h"

class FirstLayoutSkinSlipWindow;
class FirstLayoutSkinSlipDelayWindow;
class FirstLayoutSqueezeWindow;
class FirstLayoutPushWindow;
class FirstLayoutContinuousSkinSlipWindow;
class FirstLayoutContinuousSkinSlipDelayWindow;

namespace Ui {
class FirstLayoutWindow;
}

class FirstLayoutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstLayoutWindow(QWidget *parent = 0);
    ~FirstLayoutWindow();
    ServoUtility servoUtility;
    int dxl_ids_1[NUM_OF_DXL_1] = { DXL1_ID, DXL2_ID, DXL3_ID, DXL4_ID };

private slots:
    void on_goBackButton_clicked();

    void on_skinSlipButton_clicked();

    void on_skinSlipWithDelayButton_clicked();

    void on_squeezeButton_clicked();

    void on_pushButton_clicked();

    void on_continuousSkinSlipButton_clicked();

    void on_continuousSkinSlipWithDelayButton_clicked();

private:
    Ui::FirstLayoutWindow *ui;
    QWidget* parent;
    FirstLayoutSkinSlipWindow *firstLayoutSkinSlipWindow;
    FirstLayoutSkinSlipDelayWindow *firstLayoutSkinSlipDelayWindow;
    FirstLayoutSqueezeWindow *firstLayoutSqueezeWindow;
    FirstLayoutPushWindow *firstLayoutPushWindow;
    FirstLayoutContinuousSkinSlipWindow *firstLayoutContinuousSkinSlipWindow;
    FirstLayoutContinuousSkinSlipDelayWindow *firstLayoutContinuousSkinSlipDelayWindow;

};

#endif // FIRSTLAYOUTWINDOW_H
