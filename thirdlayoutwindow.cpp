#include "thirdlayoutwindow.h"
#include "ui_thirdlayoutwindow.h"
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

ThirdLayoutWindow::ThirdLayoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThirdLayoutWindow),
    parent(parent),
    thirdLayoutSqueezeWindow(new ThirdLayoutSqueezeWindow(&servoUtility, this)),
    thirdLayoutPushWindow(new ThirdLayoutPushWindow(&servoUtility, this)),
    thirdLayoutContinuousSqueezeAndPushWindow(new ThirdLayoutContinuousSqueezeAndPushWindow(&servoUtility, this))
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
    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        servoUtility.enableTorque(dxl_ids_3[i]);
    }

    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        servoUtility.setVelocity(dxl_ids_3[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPositionThirdLayout(dxl_ids_3, 0);
    qDebug() << "Servos positions have been reset!";
}

ThirdLayoutWindow::~ThirdLayoutWindow()
{
    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        servoUtility.disableTorque(dxl_ids_3[i]);
        servoUtility.setOperatingMode(dxl_ids_3[i], 3);
        servoUtility.enableTorque(dxl_ids_3[i]);
        servoUtility.setVelocity(dxl_ids_3[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPositionThirdLayout(dxl_ids_3, 0);
    qDebug() << "Servos positions have been reset!";

    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        servoUtility.disableTorque(dxl_ids_3[i]);
    }
    servoUtility.closePort();
    delete ui;
}

void ThirdLayoutWindow::on_squeezeButton_clicked()
{
    this->hide();
    thirdLayoutSqueezeWindow->show();
}


void ThirdLayoutWindow::on_pushButton_clicked()
{
    this->hide();
    thirdLayoutPushWindow->show();

}

void ThirdLayoutWindow::on_goBackButton_clicked()
{
    this->hide();
    parent->show();
    delete this;
}


void ThirdLayoutWindow::on_continuousSqueezeAndPushButton_clicked()
{
    this->hide();
    thirdLayoutContinuousSqueezeAndPushWindow->show();
}

