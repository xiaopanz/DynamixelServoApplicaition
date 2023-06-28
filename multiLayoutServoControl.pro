QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = multiLayoutServoControl
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += C:/DynamixelSDK-3.7.60/dynamixel_sdk/include/dynamixel_sdk

SOURCES += \
    firstlayoutcontinuousskinslipdelaywindow.cpp \
    firstlayoutcontinuousskinslipwindow.cpp \
    firstlayoutpushwindow.cpp \
    firstlayoutskinslipdelaywindow.cpp \
    firstlayoutskinslipwindow.cpp \
    firstlayoutsqueezewindow.cpp \
    firstlayoutwindow.cpp \
    fourthlayoutonewindow.cpp \
    fourthlayoutwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    C:/DynamixelSDK-3.7.60/dynamixel_sdk/src/dynamixel_sdk/*.cpp \
    secondlayoutcontinuousreverseskinslipwindow.cpp \
    secondlayoutcontinuousskinslipwindow.cpp \
    secondlayoutreverseskinslipwindow.cpp \
    secondlayoutskinslipwindow.cpp \
    secondlayoutwindow.cpp \
    servoutility.cpp \
    thirdlayoutcontinuoussqueezeandpushwindow.cpp \
    thirdlayoutpushwindow.cpp \
    thirdlayoutsqueezewindow.cpp \
    thirdlayoutwindow.cpp

HEADERS += \
    firstlayoutcontinuousskinslipdelaywindow.h \
    firstlayoutcontinuousskinslipwindow.h \
    firstlayoutpushwindow.h \
    firstlayoutskinslipdelaywindow.h \
    firstlayoutskinslipwindow.h \
    firstlayoutsqueezewindow.h \
    firstlayoutwindow.h \
    fourthlayoutonewindow.h \
    fourthlayoutwindow.h \
    mainwindow.h \
    secondlayoutcontinuousreverseskinslipwindow.h \
    secondlayoutcontinuousskinslipwindow.h \
    secondlayoutreverseskinslipwindow.h \
    secondlayoutskinslipwindow.h \
    secondlayoutwindow.h \
    servoutility.h \
    thirdlayoutcontinuoussqueezeandpushwindow.h \
    thirdlayoutpushwindow.h \
    thirdlayoutsqueezewindow.h \
    thirdlayoutwindow.h

FORMS += \
    firstlayoutcontinuousskinslipdelaywindow.ui \
    firstlayoutcontinuousskinslipwindow.ui \
    firstlayoutpushwindow.ui \
    firstlayoutskinslipdelaywindow.ui \
    firstlayoutskinslipwindow.ui \
    firstlayoutsqueezewindow.ui \
    firstlayoutwindow.ui \
    fourthlayoutonewindow.ui \
    fourthlayoutwindow.ui \
    mainwindow.ui \
    secondlayoutcontinuousreverseskinslipwindow.ui \
    secondlayoutcontinuousskinslipwindow.ui \
    secondlayoutreverseskinslipwindow.ui \
    secondlayoutskinslipwindow.ui \
    secondlayoutwindow.ui \
    thirdlayoutcontinuoussqueezeandpushwindow.ui \
    thirdlayoutpushwindow.ui \
    thirdlayoutsqueezewindow.ui \
    thirdlayoutwindow.ui

