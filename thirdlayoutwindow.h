#ifndef THIRDLAYOUTWINDOW_H
#define THIRDLAYOUTWINDOW_H

#include <QMainWindow>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include "thirdlayoutsqueezewindow.h"
#include "thirdlayoutpushwindow.h"
#include "thirdlayoutcontinuoussqueezeandpushwindow.h"
#include "servoutility.h"

class ThirdLayoutSqueezeWindow;
class ThirdLayoutPushWindow;
class ThirdLayoutContinuousSqueezeAndPushWindow;

namespace Ui {
class ThirdLayoutWindow;
}

class ThirdLayoutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThirdLayoutWindow(QWidget *parent = nullptr);
    ~ThirdLayoutWindow();
    ServoUtility servoUtility;
    int dxl_ids_3[NUM_OF_DXL_3] = { DXL5_ID, DXL6_ID, DXL7_ID, DXL8_ID, DXL9_ID, DXL10_ID };

private slots:
    void on_squeezeButton_clicked();

    void on_pushButton_clicked();

    void on_goBackButton_clicked();

    void on_continuousSqueezeAndPushButton_clicked();

private:
    Ui::ThirdLayoutWindow *ui;
    QWidget* parent;
    ThirdLayoutSqueezeWindow *thirdLayoutSqueezeWindow;
    ThirdLayoutPushWindow *thirdLayoutPushWindow;
    ThirdLayoutContinuousSqueezeAndPushWindow *thirdLayoutContinuousSqueezeAndPushWindow;
};

#endif // THIRDLAYOUTWINDOW_H
