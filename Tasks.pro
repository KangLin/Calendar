#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T09:35:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = Tasks
TEMPLATE = app

RC_FILE = AppIcon.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG *= C++11  

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Task.cpp \
    Tasks.cpp \
    TasksList.cpp \
    FrmFullScreen.cpp \
    TaskLockScreen.cpp \
    TaskTrayIconPrompt.cpp \
    FrmTop.cpp \
    TaskPrompt.cpp \
    FrmStickyNotes.cpp \
    FrmUpdater.cpp \
    FrmEyeNurse.cpp

HEADERS += \
        mainwindow.h \
    Task.h \
    Tasks.h \
    TasksList.h \
    FrmFullScreen.h \
    TaskLockScreen.h \
    TaskTrayIconPrompt.h \
    FrmTop.h \
    TaskPrompt.h \
    FrmStickyNotes.h \
    FrmUpdater.h \
    FrmEyeNurse.h

FORMS += \
        mainwindow.ui \
    FrmFullScreen.ui \
    FrmTop.ui \
    FrmStickyNotes.ui \
    FrmUpdater.ui \
    FrmEyeNurse.ui

RESOURCES += \
    Resource/Resource.qrc

msvc : LIBS += User32.lib

isEmpty(PREFIX) {
    android {
        PREFIX = /.
    } else {
        PREFIX = $$OUT_PWD/install
    } 
}

other.files = License.md
other.path = $$PREFIX
other.CONFIG += no_check_exist 
target.path = $$PREFIX
install.files = Install/Install.nsi
install.path = $$OUT_PWD
install.CONFIG += directory no_check_exist 
!android : INSTALLS += other target install

win32 : equals(QMAKE_HOST.os, Windows){
    
    INSTALL_TARGET = $$system_path($${PREFIX}/$(TARGET))
      
    Deployment_qtlib.target = Deployment_qtlib
    Deployment_qtlib.path = $$system_path($${PREFIX})
    Deployment_qtlib.commands = "$$system_path($$[QT_INSTALL_BINS]/windeployqt)" \
                    --compiler-runtime \
                    --verbose 7 \
                    "$${INSTALL_TARGET}"
    INSTALLS += Deployment_qtlib
}

OTHER_FILES += Install/* \
    LICENSE.md \
    appveyor.yml \
    ci/* \
    tag.sh

include(Resource/Translations/Translations.pri)
