TARGET = Tasks
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../bin
#DLLDESTDIR = $$DESTDIR

DEFINES += Tasks_EXPORTS

INCLUDEPATH+=$$PWD

#Support windows xp
QMAKE_LFLAGS *= /SUBSYSTEM:WINDOWS",5.01" 

include(../pri/Common.pri)
include(Tasks.pri)

#VERSION=1.0.0
#RC_FILE = Tasks.rc

TasksList.files = ../etc/*.xml
TasksList.path = $$PREFIX/etc/xml
TasksList.CONFIG += no_check_exist

sink.files = Resource/sink/*
sink.path = $$PREFIX/Resource
sink.CONFIG += no_check_exist

target.path = $$PREFIX/bin
INSTALLS += TasksList sink target IncludeFiles
IncludeFiles.path = $$PREFIX/include
IncludeFiles.files = $$HEADERS
INSTALLS += IncludeFiles

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
