#include "fourthlayoutwindow.h"
#include "ui_fourthlayoutwindow.h"

FourthLayoutWindow::FourthLayoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FourthLayoutWindow),
    parent(parent),
    fourthLayoutOneWindow(new FourthLayoutOneWindow(&servoUtility, this))
{
    ui->setupUi(this);
}

FourthLayoutWindow::~FourthLayoutWindow()
{
    delete ui;
}

void FourthLayoutWindow::on_goBackButton_clicked()
{
    this->hide();
    parent->show();
    delete this;
}


void FourthLayoutWindow::on_skinSlipButton_clicked()
{

}


void FourthLayoutWindow::on_continuousSkinSlipButton_clicked()
{

}


void FourthLayoutWindow::on_oneButton_clicked()
{
    this->hide();
    fourthLayoutOneWindow->show();
}


void FourthLayoutWindow::on_fourButton_clicked()
{

}

