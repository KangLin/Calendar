#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T09:35:47
#
#-------------------------------------------------

TARGET = TasksApp
TEMPLATE = app

QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network multimedia

RC_FILE = AppIcon.rc
include(../pri/Common.pri)

#VERSION=$$BUILD_VERSION
INCLUDEPATH+=$$_PRO_FILE_PWD_/../Src
DESTDIR = $$OUT_PWD/../bin
DEPENDPATH = $$DESTDIR
SOURCES += DlgAbout/DlgAbout.cpp \
    FrmEyeNurse.cpp \
    main.cpp \ 
    MainWindow.cpp \
    FrmUpdater.cpp \
    DlgOption.cpp
HEADERS += DlgAbout/DlgAbout.h \
    FrmEyeNurse.h \
    MainWindow.h \
    FrmUpdater.h \
    DlgOption.h
FORMS += DlgAbout/DlgAbout.ui \
    FrmEyeNurse.ui \
    MainWindow.ui \ 
    FrmUpdater.ui \
    DlgOption.ui
LIBS+="-L$$DESTDIR" -lTasks
