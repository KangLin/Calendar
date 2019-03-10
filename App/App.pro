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
    main.cpp \ 
    MainWindow.cpp \
    FrmUpdater.cpp \
    DlgOption.cpp
HEADERS += DlgAbout/DlgAbout.h \
    MainWindow.h \
    FrmUpdater.h \
    DlgOption.h
FORMS += DlgAbout/DlgAbout.ui \
    FrmEyeNurse.ui \
    MainWindow.ui \ 
    FrmUpdater.ui \
    DlgOption.ui
LIBS *= "-L$$DESTDIR" -lTasks

target.path = $$PREFIX/bin
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
