#include "thirdlayoutpushwindow.h"
#include "ui_thirdlayoutpushwindow.h"

ThirdLayoutPushWindow::ThirdLayoutPushWindow(ServoUtility *servoUtilityPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThirdLayoutPushWindow),
    servoUtilityPtr(servoUtilityPtr),
    parent(parent)
{
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
}

ThirdLayoutPushWindow::~ThirdLayoutPushWindow()
{
    delete ui;
}

void ThirdLayoutPushWindow::on_angleSlider_valueChanged(int value)
{
    ui->angleVal->setText(QString::number(value));
}


void ThirdLayoutPushWindow::on_velocitySlider_valueChanged(int value)
{
    ui->velocityVal->setText(QString::number(value));
}


void ThirdLayoutPushWindow::on_resetButton_clicked()
{
    ui->angleSlider->setEnabled(false);
    ui->velocitySlider->setEnabled(false);
    ui->quitButton->setEnabled(false);
    ui->resetButton->setEnabled(false);

    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_3[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_3[i], 4);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_3[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_3[i], DXL_VELOCITY_VALUE);
    }

    qDebug() << "Resetting servos positions...";
    servoUtilityPtr->resetPositionCustomThirdLayout(servoUtilityPtr->dxl_ids_3, ui->angleSlider->value(), firstReset, 1);
    firstReset = 0;
    qDebug() << "Servos positions have been reset!";

    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_3[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_3[i], 3);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_3[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_3[i], ui->velocitySlider->value());
    }
    ui->startButton->setEnabled(true);
}


void ThirdLayoutPushWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    int32_t dxls_present_position[NUM_OF_DXL_3];
    int dxls_goal_position[NUM_OF_DXL_3];
    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        dxls_present_position[i] = 0;
        dxls_goal_position[i] = 2048;

    }
    std::thread thread_sync_read(&ServoUtility::syncReadPosition, servoUtilityPtr, NUM_OF_DXL_3, servoUtilityPtr->dxl_ids_3, dxls_present_position, dxls_goal_position);
    std::thread thread_sync_write(&ServoUtility::syncWritePosition, servoUtilityPtr, NUM_OF_DXL_3, servoUtilityPtr->dxl_ids_3, dxls_goal_position);
    thread_sync_write.join();
    thread_sync_read.join();
    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_3; i++) {
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_3[i], DXL_VELOCITY_VALUE);
    }
    ui->angleSlider->setEnabled(true);
    ui->velocitySlider->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->quitButton->setEnabled(true);
    qDebug() << "Finished performing push!";
}


void ThirdLayoutPushWindow::on_quitButton_clicked()
{
    ui->startButton->setEnabled(false);
    if (firstReset == 1) {
        // Change servos velocity
        for (int i = 0; i < NUM_OF_DXL_3; i++) {
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_3[i], DXL_VELOCITY_VALUE);
        }
        qDebug() << "Resetting servos positions...";
        servoUtilityPtr->resetPosition(servoUtilityPtr->dxl_ids_3, NUM_OF_DXL_3, 0);
        qDebug() << "Servos positions have been reset!";
    } else {
        for (int i = 0; i < NUM_OF_DXL_3; i++) {
            servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_3[i]);
            servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_3[i], 4);
            servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_3[i]);
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_3[i], DXL_VELOCITY_VALUE);
        }
        qDebug() << "Resetting servos positions...";
        servoUtilityPtr->quitCustomThirdLayout(servoUtilityPtr->dxl_ids_3, 1);
        firstReset = 1;
        qDebug() << "Servos positions have been reset!";
        for (int i = 0; i < NUM_OF_DXL_3; i++) {
            servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_3[i]);
            servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_3[i], 3);
            servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_3[i]);
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_3[i], DXL_VELOCITY_VALUE);
        }
    }
    ui->angleSlider->setValue(2600);
    ui->velocitySlider->setValue(100);
    this->hide();
    parent->show();
}

