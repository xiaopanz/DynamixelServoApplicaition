#include "firstlayoutskinslipdelaywindow.h"
#include "ui_firstlayoutskinslipdelaywindow.h"

FirstLayoutSkinSlipDelayWindow::FirstLayoutSkinSlipDelayWindow(ServoUtility *servoUtilityPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstLayoutSkinSlipDelayWindow),
    servoUtilityPtr(servoUtilityPtr),
    parent(parent)
{
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
}

FirstLayoutSkinSlipDelayWindow::~FirstLayoutSkinSlipDelayWindow()
{
    delete ui;
}

void FirstLayoutSkinSlipDelayWindow::on_angleSlider_valueChanged(int value)
{
    ui->angleVal->setText(QString::number(value));
}


void FirstLayoutSkinSlipDelayWindow::on_velocitySlider_valueChanged(int value)
{
    ui->velocityVal->setText(QString::number(value));
}


void FirstLayoutSkinSlipDelayWindow::on_delaySlider_valueChanged(int value)
{
    ui->delayVal->setText(QString::number(value));
}


void FirstLayoutSkinSlipDelayWindow::on_resetButton_clicked()
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


void FirstLayoutSkinSlipDelayWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    int32_t dxls_present_position[NUM_OF_DXL_1];
    int dxls_goal_position[NUM_OF_DXL_1];
    int dxl_goal_position = 2048 - (ui->angleSlider->value() - 2048);
    int delay = ui->delaySlider->value();
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        dxls_present_position[i] = 0;
        dxls_goal_position[i] = dxl_goal_position;
    }
    int temp_dxl_ids[NUM_OF_DXL_1];
    int j = 0;
    for (int i = NUM_OF_DXL_1 - 1; i >= 0; i--) {
        temp_dxl_ids[j] = servoUtilityPtr->dxl_ids_1[i];
        j++;
    }
    std::thread thread_sync_read(&ServoUtility::syncReadPosition, servoUtilityPtr, NUM_OF_DXL_1, servoUtilityPtr->dxl_ids_1, dxls_present_position, dxls_goal_position);
    std::thread thread_sync_write(&ServoUtility::syncWritePositionWithDelay, servoUtilityPtr, NUM_OF_DXL_1, temp_dxl_ids, dxl_goal_position, delay);
    thread_sync_write.join();
    thread_sync_read.join();
    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }
    ui->angleSlider->setEnabled(true);
    ui->velocitySlider->setEnabled(true);
    ui->delaySlider->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->quitButton->setEnabled(true);
    qDebug() << "Finished performing skin slip with delay!";
}


void FirstLayoutSkinSlipDelayWindow::on_quitButton_clicked()
{
    ui->startButton->setEnabled(false);
    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }
    qDebug() << "Resetting servos positions...";
    servoUtilityPtr->resetPosition(servoUtilityPtr->dxl_ids_1, NUM_OF_DXL_1,  0);
    qDebug() << "Servos positions have been reset!";
    ui->angleSlider->setValue(2600);
    ui->velocitySlider->setValue(100);
    ui->delaySlider->setValue(200);
    this->hide();
    parent->show();
}

