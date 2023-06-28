#include "secondlayoutwindow.h"
#include "ui_secondlayoutwindow.h"
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

SecondLayoutWindow::SecondLayoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondLayoutWindow),
    parent(parent),
    secondLayoutSkinSlipWindow(new SecondLayoutSkinSlipWindow(&servoUtility, this)),
    secondLayoutReverseSkinSlipWindow(new SecondLayoutReverseSkinSlipWindow(&servoUtility, this)),
    secondLayoutContinuousSkinSlipWindow(new SecondLayoutContinuousSkinSlipWindow(&servoUtility, this)),
    secondLayoutContinuousReverseSkinSlipWindow(new SecondLayoutContinuousReverseSkinSlipWindow(&servoUtility, this))
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
    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        servoUtility.enableTorque(dxl_ids_2[i]);
    }

    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        servoUtility.setVelocity(dxl_ids_2[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPositionSecondLayout(dxl_ids_2, 0);
    qDebug() << "Servos positions have been reset!";

}

SecondLayoutWindow::~SecondLayoutWindow()
{
    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        servoUtility.disableTorque(dxl_ids_2[i]);
        servoUtility.setOperatingMode(dxl_ids_2[i], 3);
        servoUtility.enableTorque(dxl_ids_2[i]);
        servoUtility.setVelocity(dxl_ids_2[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPositionSecondLayout(dxl_ids_2, 0);
    qDebug() << "Servos positions have been reset!";

    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        servoUtility.disableTorque(dxl_ids_2[i]);
    }
    servoUtility.closePort();
    delete ui;
}

void SecondLayoutWindow::on_goBackButton_clicked()
{
    this->hide();
    parent->show();
    delete this;
}


void SecondLayoutWindow::on_skinSlipButton_clicked()
{
    this->hide();
    secondLayoutSkinSlipWindow->show();
}


void SecondLayoutWindow::on_reverseSkinSlipButton_clicked()
{
    this->hide();
    secondLayoutReverseSkinSlipWindow->show();
}


void SecondLayoutWindow::on_continuousSkinSlipButton_clicked()
{
    this->hide();
    secondLayoutContinuousSkinSlipWindow->show();
}


void SecondLayoutWindow::on_continuousReverseSkinSlipButton_clicked()
{
    this->hide();
    secondLayoutContinuousReverseSkinSlipWindow->show();
}

