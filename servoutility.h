#ifndef SERVOUTILITY_H
#define SERVOUTILITY_H

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include <QDebug>

#include "dynamixel_sdk.h"

// Control table address
#define ADDR_PRO_TORQUE_ENABLE          64                 // Control table address is different in Dynamixel model
#define ADDR_PRO_GOAL_POSITION          116
#define ADDR_PRO_PRESENT_POSITION       132
#define ADDR_PRO_PROFILE_VELOCITY       112
#define ADDR_OPERATING_MODE             11

// Data Byte Length
#define LEN_PRO_GOAL_POSITION           4
#define LEN_PRO_PRESENT_POSITION        4

// Protocol version
#define PROTOCOL_VERSION                2.0                 // See which protocol version is used in the Dynamixel

// Default setting
#define DXL1_ID                         1                   // Dynamixel#1 ID: 1
#define DXL2_ID                         2                   // Dynamixel#2 ID: 2
#define DXL3_ID                         3                   // Dynamixel#3 ID: 3
#define DXL4_ID                         4                   // Dynamixel#4 ID: 4
#define DXL5_ID                         5                   // Dynamixel#5 ID: 5
#define DXL6_ID                         6                   // Dynamixel#6 ID: 6
#define DXL7_ID                         7                   // Dynamixel#7 ID: 7
#define DXL8_ID                         8                   // Dynamixel#8 ID: 8
#define DXL9_ID                         9                   // Dynamixel#9 ID: 9
#define DXL10_ID                        10                  // Dynamixel#10 ID: 10
#define NUM_OF_DXL_1                    4                   // Number of Dynamixels for First Layout
#define NUM_OF_DXL_2                    6                   // Number of Dynamixels for Second Layout
#define NUM_OF_DXL_3                    6                   // Number of Dynamixels for Third Layout
#define NUM_OF_DXL_4                    6                   // Number of Dynamixels for Fourth Layout
#define BAUDRATE                        1000000
#define DEVICENAME                      "COM3"              // Check which port is being used on your controller
// ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      0                   // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      1024                // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MOVING_STATUS_THRESHOLD     20                  // Dynamixel moving status threshold
#define DXL_VELOCITY_VALUE              100                 // rotating velocity of Dynamixels
#define DXL_VELOCITY_RESET_VALUE        0                   // reset value of velocity for Dynamixels
#define ESC_ASCII_VALUE                 0x1b


class ServoUtility
{
public:
    ServoUtility();
    ~ServoUtility();
    bool openPort();
    void closePort();
    bool setBaudRate(int baud_rate);
    void enableTorque(int dxl_id);
    void disableTorque(int dxl_id);
    void setVelocity(int dxl_id, int velocity);
    void resetVelocity(int dxl_id);
    void syncReadPosition(int dxl_num, int dxl_ids[], int32_t dxls_present_position[], int dxls_goal_position[]);
    void syncWritePosition(int dxl_num, int dxl_ids[], int dxls_goal_position[]);
    void writePositionWithDelay(int dxl_id, int dxl_goal_position, int delay);
    void syncWritePositionWithDelay(int dxl_num, int dxl_ids[], int dxl_goal_position, int delay);
    void resetPositionFirstLayout(int dxl_ids[], int dxl_goal_position);
    void resetPositionSecondLayout(int dxl_ids[], int dxl_goal_position);
    void resetPositionThirdLayout(int dxl_ids[], int dxl_goal_position);
    void setOperatingMode(int dxl_id, uint8_t operating_mode);
    void resetPositionCustomFirstLayout(int dxl_ids[], int dxl_goal_position, int firstReset, int flag);
    void resetPositionCustomSecondLayout(int dxl_ids[], int dxl_goal_position, int firstReset);
    void resetPositionCustomThirdLayout(int dxl_ids[], int dxl_goal_position, int firstReset, int flag);
    void quitCustomFirstLayout(int dxl_ids[], int flag);
    void quitCustomSecondLayout(int dxl_ids[]);
    void quitCustomThirdLayout(int dxl_ids[], int flag);
    int dxl_ids_1[NUM_OF_DXL_1] = { DXL1_ID, DXL2_ID, DXL3_ID, DXL4_ID };
    int dxl_ids_2[NUM_OF_DXL_2] = { DXL5_ID, DXL6_ID, DXL7_ID, DXL8_ID, DXL9_ID, DXL10_ID };
    int dxl_ids_3[NUM_OF_DXL_3] = { DXL5_ID, DXL6_ID, DXL7_ID, DXL8_ID, DXL9_ID, DXL10_ID };
    int dxl_ids_4[NUM_OF_DXL_4] = { DXL5_ID, DXL9_ID, DXL7_ID, DXL8_ID, DXL6_ID, DXL10_ID };
private:
    dynamixel::PortHandler* portHandler;
    dynamixel::PacketHandler* packetHandler;
    dynamixel::GroupSyncWrite groupSyncWrite;
    dynamixel::GroupSyncRead groupSyncRead;
    int dxl_comm_result;
    uint8_t dxl_error;
    bool dxl_addparam_result;
    uint8_t param_goal_position[4];
    bool dxl_getdata_result;
    std::mutex mtx;
};

#endif // SERVOUTILITY_H
