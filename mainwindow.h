#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "firstlayoutwindow.h"
#include "secondlayoutwindow.h"
#include "thirdlayoutwindow.h"
#include "fourthlayoutwindow.h"

class FirstLayoutWindow;
class SecondLayoutWindow;
class ThirdLayoutWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_firstLayoutButton_clicked();

    void on_secondLayoutButton_clicked();

    void on_thirdLayoutButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    FirstLayoutWindow *firstLayoutWindow;
    SecondLayoutWindow *secondLayoutWindow;
    ThirdLayoutWindow *thirdLayoutWindow;
    FourthLayoutWindow *fourthLayoutWindow;
};
#endif // MAINWINDOW_H
