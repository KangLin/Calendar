QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network multimedia

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG *= C++11
msvc {
    QMAKE_CXXFLAGS += "/utf-8"
    QMAKE_LFLAGS *= /SUBSYSTEM:WINDOWS",5.01"
    LIBS += User32.lib
}
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Task.cpp \
    Tasks.cpp \
    TasksList.cpp \
    TaskLockScreen.cpp \
    TaskTrayIconPrompt.cpp \
    FrmTop.cpp \
    TaskPrompt.cpp \
    FrmStickyNotes.cpp \
    Global/GlobalDir.cpp \
    Global/Log.cpp \
    FrmFullScreen.cpp \
    Global/Tool.cpp \
    FrmTaskPropery.cpp \
    ViewTaskProperty.cpp \ 
    FrmTasks.cpp \  
    TaskPromptDelay.cpp \
    $$PWD/FrmTasksList.cpp

HEADERS += \
    Task.h \
    Tasks.h \
    TasksList.h \
    TaskLockScreen.h \
    TaskTrayIconPrompt.h \
    FrmTop.h \
    TaskPrompt.h \
    FrmStickyNotes.h \
    Global/GlobalDir.h \
    Global/Log.h \
    FrmFullScreen.h \
    ObjectFactory.h \
    Global/Tool.h \
    FrmTaskPropery.h \
    ViewTaskProperty.h \ 
    FrmTasks.h \  
    TaskPromptDelay.h \
    $$PWD/FrmTasksList.h

FORMS += \
    FrmFullScreen.ui \
    FrmTop.ui \
    FrmStickyNotes.ui \
    FrmTaskProperty.ui \ 
    FrmTasks.ui \
    $$PWD/FrmTasksList.ui

RESOURCES += \
    Resource/Resource.qrc \
    Resource/sink/dark/style.qrc

isEmpty(PREFIX) {
    android {
        PREFIX = /.
    } else {
        PREFIX = $$OUT_PWD/install
    } 
}

DISTFILES += Resource/sink/* 

include(Resource/Translations/Translations.pri)

TasksList.files = etc/*.xml
TasksList.path = $$PREFIX/etc/xml
TasksList.CONFIG += no_check_exist

sink.files = Resource/sink/*
sink.path = $$PREFIX/Resource
sink.CONFIG += no_check_exist
INSTALLS += TasksList sink
