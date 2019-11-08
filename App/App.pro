#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T09:35:47
#
#-------------------------------------------------

TARGET = TasksApp
TEMPLATE = app

QT += core gui xml sql
android: QT += androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network multimedia

RC_FILE = AppIcon.rc
include(../pri/Common.pri)
include(../pri/Translations.pri)

CONFIG(staticlib): CONFIG*=static
CONFIG(static): DEFINES *= TASKS_STATIC_DEFINE

isEmpty(RabbitCommon_DIR): RabbitCommon_DIR=$$(RabbitCommon_DIR)
isEmpty(RabbitCommon_DIR): RabbitCommon_DIR=$$PWD/../../RabbitCommon
!isEmpty(RabbitCommon_DIR): exists("$${RabbitCommon_DIR}/Src/Src.pro"){
    CONFIG(static): DEFINES *= RABBITCOMMON_STATIC_DEFINE LUNARCALENDAR_STATIC_DEFINE
} else {
    message("Don't find RabbitCommon, in RabbitCommon_DIR:$$RabbitCommon_DIR")
    message("1. Please download RabbitCommon source code from https://github.com/KangLin/RabbitCommon ag:")
    message("   git clone https://github.com/KangLin/RabbitCommon.git")
    error  ("2. Then set value RabbitCommon_DIR to download dirctory")
}

DEFINES += RABBITCOMMON
INCLUDEPATH+=$$_PRO_FILE_PWD_/../Src $$_PRO_FILE_PWD_/../Src/export $${RabbitCommon_DIR}/Src $${RabbitCommon_DIR}/Src/export
DESTDIR = $$OUT_PWD/../bin
DEPENDPATH = $$DESTDIR
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    DlgOption.cpp
HEADERS += \
    MainWindow.h \
    DlgOption.h
FORMS += \
    FrmEyeNurse.ui \
    MainWindow.ui \
    DlgOption.ui

LIBS *= "-L$$DESTDIR" -lRabbitCommon -lLunarCalendar -lTasks

win32 {
    QT += winextras
    LIBS += -lAdvapi32 -lOle32 -lShell32
} else:mac {
    QT += macextras
    LIBS += -framework Security
} else:unix:!android {
    QT += dbus
    LIBS += -lutil
}

!android: target.path = $$PREFIX/bin
INSTALLS += target

win32 : equals(QMAKE_HOST.os, Windows){
    
    INSTALL_TARGET = $$system_path($${PREFIX}/bin/$(TARGET))

    Deployment_qtlib.target = Deployment_qtlib
    Deployment_qtlib.path = $$system_path($${PREFIX})
    Deployment_qtlib.commands = "$$system_path($$[QT_INSTALL_BINS]/windeployqt)" \
                    --compiler-runtime \
                    --verbose 7 \
                    "$${INSTALL_TARGET}"
    INSTALLS += Deployment_qtlib
}

OTHER_FILES += CMakeLists.txt

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/res/values/* \
    android/res/values-zh/*

#contains(ANDROID_TARGET_ARCH,x86) {
android: ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
