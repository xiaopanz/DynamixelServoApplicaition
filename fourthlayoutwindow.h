#ifndef FOURTHLAYOUTWINDOW_H
#define FOURTHLAYOUTWINDOW_H

#include "fourthlayoutonewindow.h"
#include "servoutility.h"
#include <QMainWindow>

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
};

#endif // FOURTHLAYOUTWINDOW_H
