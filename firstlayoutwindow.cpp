#include "firstlayoutwindow.h"
#include "ui_firstlayoutwindow.h"
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

FirstLayoutWindow::FirstLayoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstLayoutWindow),
    parent(parent),
    firstLayoutSkinSlipWindow(new FirstLayoutSkinSlipWindow(&servoUtility, this)),
    firstLayoutSkinSlipDelayWindow(new FirstLayoutSkinSlipDelayWindow(&servoUtility, this)),
    firstLayoutSqueezeWindow(new FirstLayoutSqueezeWindow(&servoUtility, this)),
    firstLayoutPushWindow(new FirstLayoutPushWindow(&servoUtility, this)),
    firstLayoutContinuousSkinSlipWindow(new FirstLayoutContinuousSkinSlipWindow(&servoUtility, this)),
    firstLayoutContinuousSkinSlipDelayWindow(new FirstLayoutContinuousSkinSlipDelayWindow(&servoUtility, this))
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
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtility.enableTorque(dxl_ids_1[i]);
    }

    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtility.setVelocity(dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPosition(dxl_ids_1, NUM_OF_DXL_1, 0);
    qDebug() << "Servos positions have been reset!";

}

FirstLayoutWindow::~FirstLayoutWindow()
{
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtility.disableTorque(dxl_ids_1[i]);
        servoUtility.setOperatingMode(dxl_ids_1[i], 3);
        servoUtility.enableTorque(dxl_ids_1[i]);
        servoUtility.setVelocity(dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }

    // Reset servos initial position
    qDebug() << "Resetting servos positions...";
    servoUtility.resetPosition(dxl_ids_1, NUM_OF_DXL_1, 0);
    qDebug() << "Servos positions have been reset!";

    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtility.disableTorque(dxl_ids_1[i]);
    }
    servoUtility.closePort();
    delete ui;

}

void FirstLayoutWindow::on_goBackButton_clicked()
{
    this->hide();
    parent->show();
    delete this;
}


void FirstLayoutWindow::on_skinSlipButton_clicked()
{
    this->hide();
    firstLayoutSkinSlipWindow->show();
}


void FirstLayoutWindow::on_skinSlipWithDelayButton_clicked()
{
    this->hide();
    firstLayoutSkinSlipDelayWindow->show();
}


void FirstLayoutWindow::on_squeezeButton_clicked()
{
    this->hide();
    firstLayoutSqueezeWindow->show();
}


void FirstLayoutWindow::on_pushButton_clicked()
{
    this->hide();
    firstLayoutPushWindow->show();
}


void FirstLayoutWindow::on_continuousSkinSlipButton_clicked()
{
    this->hide();
    firstLayoutContinuousSkinSlipWindow->show();
}


void FirstLayoutWindow::on_continuousSkinSlipWithDelayButton_clicked()
{
    this->hide();
    firstLayoutContinuousSkinSlipDelayWindow->show();
}

