#ifndef FOURTHLAYOUTONEWINDOW_H
#define FOURTHLAYOUTONEWINDOW_H

#include "servoutility.h"

#include <QMainWindow>

namespace Ui {
class FourthLayoutOneWindow;
}

class FourthLayoutOneWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FourthLayoutOneWindow(ServoUtility *servoUtilityPtr, QWidget *parent = 0);
    ~FourthLayoutOneWindow();

private slots:
    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::FourthLayoutOneWindow *ui;
    ServoUtility *servoUtilityPtr;
    QWidget* parent;
    int firstReset = 1;
};

#endif // FOURTHLAYOUTONEWINDOW_H
