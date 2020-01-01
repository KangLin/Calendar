TARGET = Tasks
TEMPLATE = lib

DESTDIR = $$OUT_PWD/../bin
#DLLDESTDIR = $$DESTDIR

CONFIG += link_pkgconfig create_prl link_prl
CONFIG(staticlib): CONFIG*=static

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
INCLUDEPATH += $$_PRO_FILE_PWD_/../3th_libs/LunarCalendar/Src \
    $$_PRO_FILE_PWD_/../3th_libs/LunarCalendar/Src/export \
    $${RabbitCommon_DIR}/Src \
    $${RabbitCommon_DIR}/Src/export

LIBS *= -L$$DESTDIR
android{
    versionAtLeast(QT_VERSION, 5.14.0) : LIBS *= -lRabbitCommon_$${ANDROID_TARGET_ARCH} -lLunarCalendar_$${ANDROID_TARGET_ARCH}
    else: LIBS *= -lRabbitCommon -lLunarCalendar
} else{
    LIBS *= -lRabbitCommon -lLunarCalendar
}

include(../pri/Common.pri)
include(Tasks.pri)

#VERSION=1.0.0
#RC_FILE = Tasks.rc

TasksList.files = ../etc/*.xml
android: TasksList.path = $$PREFIX/assets/etc/xml
else: TasksList.path = $$PREFIX/etc/xml
TasksList.CONFIG += no_check_exist

IncludeFiles.path = $$PREFIX/include/Tasks
IncludeFiles.files = $$INSTALLHEADER_FILES
!android: unix: target.path = $$PREFIX/lib
else: target.path = $$PREFIX/bin
INSTALLS += TasksList target IncludeFiles

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
