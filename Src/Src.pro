TARGET = Tasks
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../bin
#DLLDESTDIR = $$DESTDIR

CONFIG += link_pkgconfig create_prl link_prl
CONFIG(staticlib): CONFIG*=static
#android: CONFIG*=static

INCLUDEPATH+=$$_PRO_FILE_PWD_/../3th_libs/LunarCalendar/Src $$_PRO_FILE_PWD_/../3th_libs/LunarCalendar/Src/export 
LIBS *= "-L$$OUT_PWD/../bin" -lLunarCalendar

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

IncludeFiles.path = $$PREFIX/include/Tasks
IncludeFiles.files = $$INSTALLHEADER_FILES
!android: target.path = $$PREFIX/bin
INSTALLS += TasksList sink target IncludeFiles

!CONFIG(static): win32 : equals(QMAKE_HOST.os, Windows){
    
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
