#include "fourthlayoutonewindow.h"
#include "ui_fourthlayoutonewindow.h"

FourthLayoutOneWindow::FourthLayoutOneWindow(ServoUtility *servoUtilityPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FourthLayoutOneWindow),
    servoUtilityPtr(servoUtilityPtr),
    parent(parent)
{
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
}

FourthLayoutOneWindow::~FourthLayoutOneWindow()
{
    delete ui;
}

void FourthLayoutOneWindow::on_resetButton_clicked()
{
    ui->quitButton->setEnabled(false);
    ui->resetButton->setEnabled(false);

    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_1[i], 4);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }
    qDebug() << "Resetting servos positions...";
    servoUtilityPtr->resetPositionCustomFirstLayout(servoUtilityPtr->dxl_ids_1, 2048, firstReset, 0);
    firstReset = 0;
    qDebug() << "Servos positions have been reset!";
    for (int i = 0; i < NUM_OF_DXL_1; i++) {
        servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_1[i], 3);
        servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_1[i]);
        servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
    }

    ui->startButton->setEnabled(true);
}


void FourthLayoutOneWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    int32_t dxls_present_position[NUM_OF_DXL_4/2];
    int dxls_goal_position[NUM_OF_DXL_4/2];
    for (int i = 0; i < NUM_OF_DXL_4/2; i++) {
        dxls_present_position[i] = 0;
        dxls_goal_position[i] = 2048;
    }
    int dxl_for_one[NUM_OF_DXL_4/2] = { DXL5_ID, DXL9_ID, DXL7_ID };
    std::thread thread_sync_read(&ServoUtility::syncReadPosition, servoUtilityPtr, NUM_OF_DXL_1/2, dxl_for_one, dxls_present_position, dxls_goal_position);
    std::thread thread_sync_write(&ServoUtility::syncWritePosition, servoUtilityPtr, NUM_OF_DXL_1/2, dxl_for_one, dxls_goal_position);
    thread_sync_write.join();
    thread_sync_read.join();
    // Change servos velocity
    for (int i = 0; i < NUM_OF_DXL_4/2; i++) {
        servoUtilityPtr->setVelocity(dxl_for_one[i], DXL_VELOCITY_VALUE);
    }
    ui->resetButton->setEnabled(true);
    ui->quitButton->setEnabled(true);
    qDebug() << "Finished performing One!";
}


void FourthLayoutOneWindow::on_quitButton_clicked()
{
    ui->startButton->setEnabled(false);
    if (firstReset == 1) {
        // Change servos velocity
        for (int i = 0; i < NUM_OF_DXL_1; i++) {
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
        }
        qDebug() << "Resetting servos positions...";
        servoUtilityPtr->resetPositionFirstLayout(servoUtilityPtr->dxl_ids_1, 0);
        qDebug() << "Servos positions have been reset!";
    } else {
        for (int i = 0; i < NUM_OF_DXL_1; i++) {
            servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_1[i]);
            servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_1[i], 4);
            servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_1[i]);
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
        }
        qDebug() << "Resetting servos positions...";
        servoUtilityPtr->quitCustomFirstLayout(servoUtilityPtr->dxl_ids_1, 0);
        firstReset = 1;
        qDebug() << "Servos positions have been reset!";
        for (int i = 0; i < NUM_OF_DXL_1; i++) {
            servoUtilityPtr->disableTorque(servoUtilityPtr->dxl_ids_1[i]);
            servoUtilityPtr->setOperatingMode(servoUtilityPtr->dxl_ids_1[i], 3);
            servoUtilityPtr->enableTorque(servoUtilityPtr->dxl_ids_1[i]);
            servoUtilityPtr->setVelocity(servoUtilityPtr->dxl_ids_1[i], DXL_VELOCITY_VALUE);
        }
    }

    // ui->angleSlider->setValue(2600);
    // ui->velocitySlider->setValue(100);
    this->hide();
    parent->show();
}

