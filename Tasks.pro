#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T09:35:47
#
#-------------------------------------------------

TARGET = Tasks
TEMPLATE = app

#Get app version use git, please set git path to environment variable PATH
isEmpty(BUILD_VERSION) {
    isEmpty(GIT) : GIT=$$(GIT)
    isEmpty(GIT) : GIT=git
    isEmpty(GIT_DESCRIBE) {
        GIT_DESCRIBE = $$system(cd $$system_path($$PWD) && $$GIT describe --tags)
        isEmpty(BUILD_VERSION) {
            BUILD_VERSION = $$GIT_DESCRIBE
        }
    }
    isEmpty(BUILD_VERSION) {
        BUILD_VERSION = $$system(cd $$system_path($$PWD) && $$GIT rev-parse --short HEAD)
    }
    
    isEmpty(BUILD_VERSION){
        error("Built without git, please add BUILD_VERSION to DEFINES or add git path to environment variable GIT or qmake parameter GIT")
    }
}
message("BUILD_VERSION:$$BUILD_VERSION")
DEFINES += BUILD_VERSION=\"\\\"$$quote($$BUILD_VERSION)\\\"\"

contains(QMAKE_TARGET.arch, x86_64) {
    DEFINES += BUILD_ARCH=\"\\\"x86_64\\\"\"
} else {
    DEFINES += BUILD_ARCH=\"\\\"x86\\\"\"
}

RC_FILE = AppIcon.rc

include(Tasks.pri)

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

other.files = License.md Authors.md AppIcon.ico
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
    appveyor.yml \
    ci/* \
    tag.sh \
    Update.xml

DISTFILES += \
    LICENSE.md \
    Authors.md \
    README_zh_CN.md \
    README.md 
