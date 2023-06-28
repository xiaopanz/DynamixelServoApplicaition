#include "secondlayoutcontinuousskinslipwindow.h"
#include "ui_secondlayoutcontinuousskinslipwindow.h"

SecondLayoutContinuousSkinSlipWindow::SecondLayoutContinuousSkinSlipWindow(ServoUtility *servoUtilityPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondLayoutContinuousSkinSlipWindow),
    servoUtilityPtr(servoUtilityPtr),
    parent(parent)
{
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
}

SecondLayoutContinuousSkinSlipWindow::~SecondLayoutContinuousSkinSlipWindow()
{
    delete ui;
}

void SecondLayoutContinuousSkinSlipWindow::on_angleSlider_valueChanged(int value)
{
    ui->angleVal->setText(QString::number(value));
}


void SecondLayoutContinuousSkinSlipWindow::on_velocitySlider_valueChanged(int value)
{
    ui->velocityVal->setText(QString::number(value));
}


void SecondLayoutContinuousSkinSlipWindow::on_resetButton_clicked()
{
    ui->angleSlider->setEnabled(false);
    ui->velocitySlider->setEnabled(false);
    ui->quitButton->setEnabled(false);
    ui->resetButton->setEnabled(false);

    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_2[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_2[i], 4);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_2[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_2[i], DXL_VELOCITY_VALUE);
    }

    qDebug() << "Resetting servos positions...";
    servoUtilityPtr->resetPositionCustomSecondLayout(servoUtilityPtr->dxl_ids_2, ui->angleSlider->value() , firstReset);
    firstReset = 0;
    qDebug() << "Servos positions have been reset!";

    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_2[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_2[i], 3);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_2[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_2[i], ui->velocitySlider->value());
    }
    ui->startButton->setEnabled(true);
}


void SecondLayoutContinuousSkinSlipWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    int direction = 0;
    int32_t dxls_present_position[NUM_OF_DXL_2];
    int dxls_goal_position_0[NUM_OF_DXL_2];
    int dxls_goal_position_1[NUM_OF_DXL_2];
    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        dxls_present_position[i] = 0;
        if (i < NUM_OF_DXL_2 / 2) {
            dxls_goal_position_0[i] =2048 - (ui->angleSlider->value() - 2048);
            dxls_goal_position_1[i] =ui->angleSlider->value();
        }
        else {
            dxls_goal_position_0[i] = ui->angleSlider->value();
            dxls_goal_position_1[i] =2048 - (ui->angleSlider->value() - 2048);
        }
    }

    int iteration = 0;
    while (iteration != 10) {
        if (direction == 0) {
            std::thread thread_sync_read(&ServoUtility::syncReadPosition, servoUtilityPtr, NUM_OF_DXL_2, servoUtilityPtr->dxl_ids_2, dxls_present_position, dxls_goal_position_0);
            std::thread thread_sync_write(&ServoUtility::syncWritePosition, servoUtilityPtr, NUM_OF_DXL_2, servoUtilityPtr->dxl_ids_2, dxls_goal_position_0);
            thread_sync_write.join();
            thread_sync_read.join();
        }
        else {
            std::thread thread_sync_read(&ServoUtility::syncReadPosition, servoUtilityPtr, NUM_OF_DXL_2, servoUtilityPtr->dxl_ids_2, dxls_present_position, dxls_goal_position_1);
            std::thread thread_sync_write(&ServoUtility::syncWritePosition, servoUtilityPtr, NUM_OF_DXL_2, servoUtilityPtr->dxl_ids_2, dxls_goal_position_1);
            thread_sync_write.join();
            thread_sync_read.join();
        }
        if (direction == 0) {
            direction = 1;
        }
        else {
            direction = 0;
        }
        iteration++;
    }
    std::thread thread_sync_read(&ServoUtility::syncReadPosition, servoUtilityPtr, NUM_OF_DXL_2, servoUtilityPtr->dxl_ids_2, dxls_present_position, dxls_goal_position_0);
    std::thread thread_sync_write(&ServoUtility::syncWritePosition, servoUtilityPtr, NUM_OF_DXL_2, servoUtilityPtr->dxl_ids_2, dxls_goal_position_0);
    thread_sync_write.join();
    thread_sync_read.join();
    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_2; i++) {
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_2[i], DXL_VELOCITY_VALUE);
    }
    ui->angleSlider->setEnabled(true);
    ui->velocitySlider->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->quitButton->setEnabled(true);
    qDebug() << "Finished performing continuous skin slip!";
}


void SecondLayoutContinuousSkinSlipWindow::on_quitButton_clicked()
{
    ui->startButton->setEnabled(false);
    if (firstReset == 1) {
        // Change servos velocity
        for (int i = 0; i < NUM_OF_DXL_2; i++) {
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_2[i], DXL_VELOCITY_VALUE);
        }
        qDebug() << "Resetting servos positions...";
        servoUtilityPtr->resetPositionSecondLayout(servoUtilityPtr->dxl_ids_2, 0);
        qDebug() << "Servos positions have been reset!";
    } else {
        for (int i = 0; i < NUM_OF_DXL_2; i++) {
            servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_2[i]);
            servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_2[i], 4);
            servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_2[i]);
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_2[i], DXL_VELOCITY_VALUE);
        }
        qDebug() << "Resetting servos positions...";
        servoUtilityPtr->quitCustomSecondLayout(servoUtilityPtr->dxl_ids_2);
        firstReset = 1;
        qDebug() << "Servos positions have been reset!";
        for (int i = 0; i < NUM_OF_DXL_2; i++) {
            servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_2[i]);
            servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_2[i], 3);
            servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_2[i]);
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_2[i], DXL_VELOCITY_VALUE);
        }
    }
    ui->angleSlider->setValue(2600);
    ui->velocitySlider->setValue(100);
    this->hide();
    parent->show();
}

