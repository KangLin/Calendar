#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T09:35:47
#
#-------------------------------------------------

TEMPLATE = subdirs
DESTDIR = $$OUT_PWD/bin

RabbitCommon.file = 3th_libs/RabbitCommon.pro
LunarCalendar.file = 3th_libs/LunarCalendar.pro
lib.subdir = Src
App.depends = RabbitCommon LunarCalendar lib
CONFIG *= ordered
SUBDIRS = RabbitCommon LunarCalendar lib App

isEmpty(PREFIX) {
    qnx : PREFIX = /tmp
    else : ios: PREFIX=/
    else : android : PREFIX = /
    else : unix : PREFIX = /opt/Tasks
    else : PREFIX = $$OUT_PWD/install
}
other.files = License.md Authors.md ChangeLog.md Authors_zh_CN.md \
              ChangeLog_zh_CN.md App/AppIcon.ico
android: other.path = $$PREFIX/assets
else: other.path = $$PREFIX
other.CONFIG += no_check_exist 
INSTALLS += other

install.files = Install/Install.nsi
install.path = $$OUT_PWD
install.CONFIG += directory no_check_exist 
win32:  INSTALLS += install

!android : unix {
    DESKTOP_FILE.target = DESKTOP_FILE
    DESKTOP_FILE.files = $$PWD/debian/Tasks.desktop
    DESKTOP_FILE.path = $$system_path($${PREFIX})/share/applications
    DESKTOP_FILE.CONFIG += directory no_check_exist

    # install icons
    icon128.target = icon128
    icon128.files = Src/Resource/image/Tasks.png
    icon128.path = $${PREFIX}/share/pixmaps
    icon128.CONFIG = directory no_check_exist

    INSTALLS += DESKTOP_FILE icon128
}

OTHER_FILES += Install/* \
    appveyor.yml \
    ci/* \
    tag.sh \ 
    Update/* \
    CMakeLists.txt \
    etc/* \
    cmake/* \
    .travis.yml \
    debian/* \
    test/* \
    build_debpackage.sh

DISTFILES += \
    LICENSE.md \
    Authors.md \
    Authors_zh_CN.md \
    README_zh_CN.md \
    README.md \ 
    ChangeLog.md \
    ChangeLog_zh_CN.md 

RESOURCES += \
    Src/Resource/Resource.qrc \
    App/Resource/Resource.qrc \ 
    Src/Resource/ResourceTasks.qrc
   
