#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_firstLayoutButton_clicked()
{
    this->hide();
    firstLayoutWindow = new FirstLayoutWindow(this);
    firstLayoutWindow->show();
}


void MainWindow::on_secondLayoutButton_clicked()
{
    this->hide();
    secondLayoutWindow = new SecondLayoutWindow(this);
    secondLayoutWindow->show();
}


void MainWindow::on_thirdLayoutButton_clicked()
{
    this->hide();
    thirdLayoutWindow = new ThirdLayoutWindow(this);
    thirdLayoutWindow->show();
}


void MainWindow::on_pushButton_clicked()
{
    this->hide();
    fourthLayoutWindow = new FourthLayoutWindow(this);
    fourthLayoutWindow->show();
}

