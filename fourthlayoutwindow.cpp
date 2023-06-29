#include "fourthlayoutwindow.h"
#include "ui_fourthlayoutwindow.h"
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

FourthLayoutWindow::FourthLayoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FourthLayoutWindow),
    parent(parent),
    fourthLayoutOneWindow(new FourthLayoutOneWindow(&servoUtility, this))
{
    ui->setupUi(this);

    // Open port
    if (!servoUtility.openPort())
    {
        QTimer::singleShot(0, QCoreApplication::instance(), &QCoreApplication::quit);
        return;
    }

    // Set port baudrate
    if (!servoUtility.setBaudRate(BAUDRATE)) {
        QTimer::singleShot(0, QCoreApplication::instance(), &QCoreApplication::quit);
        return;
    }

    // Enable servos torque
    for (int i = 0; i < NUM_OF_DXL_4; i++) {
        servoUtility.enableTorque(dxl_ids_4[i]);
    }

    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_4; i++) {
        servoUtility.setVelocity(dxl_ids_4[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPosition(dxl_ids_4, NUM_OF_DXL_4, 0);
    qDebug() << "Servos positions have been reset!";
}

FourthLayoutWindow::~FourthLayoutWindow()
{
    for (int i = 0; i < NUM_OF_DXL_4; i++) {
        servoUtility.disableTorque(dxl_ids_4[i]);
        servoUtility.setOperatingMode(dxl_ids_4[i], 3);
        servoUtility.enableTorque(dxl_ids_4[i]);
        servoUtility.setVelocity(dxl_ids_4[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPosition(dxl_ids_4, NUM_OF_DXL_4, 0);
    qDebug() << "Servos positions have been reset!";

    for (int i = 0; i < NUM_OF_DXL_4; i++) {
        servoUtility.disableTorque(dxl_ids_4[i]);
    }
    servoUtility.closePort();
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

