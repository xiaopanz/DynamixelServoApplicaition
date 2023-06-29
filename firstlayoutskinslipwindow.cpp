#include "firstlayoutskinslipwindow.h"
#include "ui_firstlayoutskinslipwindow.h"

FirstLayoutSkinSlipWindow::FirstLayoutSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstLayoutSkinSlipWindow),
    servoUtilityPtr(servoUtilityPtr),
    parent(parent)
{
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
}

FirstLayoutSkinSlipWindow::~FirstLayoutSkinSlipWindow()
{
    delete ui;
}

void FirstLayoutSkinSlipWindow::on_angleSlider_valueChanged(int value)
{
    ui->angleVal->setText(QString::number(value));
}


void FirstLayoutSkinSlipWindow::on_velocitySlider_valueChanged(int value)
{
    ui->velocityVal->setText(QString::number(value));
}


void FirstLayoutSkinSlipWindow::on_resetButton_clicked()
{
    ui->angleSlider->setEnabled(false);
    ui->velocitySlider->setEnabled(false);
    ui->quitButton->setEnabled(false);
    ui->resetButton->setEnabled(false);

    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_1[i], 4);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }
    qDebug() << "Resetting servos positions...";
    servoUtilityPtr->resetPosition(servoUtilityPtr->dxl_ids_1, NUM_OF_DXL_1, ui->angleSlider->value() - 4096);
    qDebug() << "Servos positions have been reset!";
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_1[i], 3);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], ui->velocitySlider->value());
    }

    ui->startButton->setEnabled(true);
}


void FirstLayoutSkinSlipWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    int32_t dxls_present_position[NUM_OF_DXL_1];
    int dxls_goal_position[NUM_OF_DXL_1];
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        dxls_present_position[i] = 0;
        dxls_goal_position[i] = 2048 - (ui->angleSlider->value() - 2048);
    }
    std::thread thread_sync_read(&ServoUtility::syncReadPosition, servoUtilityPtr, NUM_OF_DXL_1, servoUtilityPtr->dxl_ids_1, dxls_present_position, dxls_goal_position);
    std::thread thread_sync_write(&ServoUtility::syncWritePosition, servoUtilityPtr, NUM_OF_DXL_1, servoUtilityPtr->dxl_ids_1, dxls_goal_position);
    thread_sync_write.join();
    thread_sync_read.join();
    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }
    ui->angleSlider->setEnabled(true);
    ui->velocitySlider->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->quitButton->setEnabled(true);
    qDebug() << "Finished performing skin slip!";
}


void FirstLayoutSkinSlipWindow::on_quitButton_clicked()
{
    ui->startButton->setEnabled(false);
    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }
    qDebug() << "Resetting servos positions...";
    servoUtilityPtr->resetPosition(servoUtilityPtr->dxl_ids_1, NUM_OF_DXL_1, 0);
    qDebug() << "Servos positions have been reset!";
    ui->angleSlider->setValue(2600);
    ui->velocitySlider->setValue(100);
    this->hide();
    parent->show();
}

