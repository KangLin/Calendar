# 作者：康林 <kl222@126.com>

TEMPLATE = subdirs
DESTDIR = $$OUT_PWD/bin

RabbitCommon.file = 3th_libs/RabbitCommon.pro
LunarCalendar.file = 3th_libs/LunarCalendar.pro
LunarCalendar.depends = RabbitCommon
lib.subdir = Src
lib.depends = LunarCalendar
App.depends = RabbitCommon LunarCalendar lib
CONFIG *= ordered
SUBDIRS = RabbitCommon LunarCalendar lib App

isEmpty(PREFIX) {
    android {
        PREFIX = /.
    } else {
        PREFIX = $$OUT_PWD/../install
    } 
}
other.files = License.md Authors.md ChangeLog.md Authors_zh_CN.md \
              ChangeLog_zh_CN.md
win32: other.files += App/AppIcon.ico #windows install need
android: other.path = $$PREFIX/assets
else: other.path = $$PREFIX
other.CONFIG += no_check_exist
INSTALLS += other

install_win.files = Install/Install.nsi
install_win.path = $$OUT_PWD
install_win.CONFIG += directory no_check_exist 
win32:  INSTALLS += install_win

install_unix.files = Install/install.sh
install_unix.path = $$PREFIX
install_unix.CONFIG += directory no_check_exist 
unix: !android: INSTALLS += install_unix

!android : unix {
    DESKTOP_FILE.target = DESKTOP_FILE
    DESKTOP_FILE.files = $$PWD/share/org.Rabbit.Calendar.desktop
    DESKTOP_FILE.path = $${PREFIX}/share/applications
    DESKTOP_FILE.CONFIG += directory no_check_exist

    START_SCRIPT.target = START_SCRIPT
    START_SCRIPT.files = $$PWD/share/Calendar.sh
    START_SCRIPT.path = $${PREFIX}/bin
    START_SCRIPT.CONFIG += directory no_check_exist
    
    # install icons
    icon128.target = icon128
    icon128.files = Src/Resource/image/Calendar.png
    icon128.path = $${PREFIX}/share/pixmaps
    icon128.CONFIG = directory no_check_exist

    INSTALLS += DESKTOP_FILE START_SCRIPT icon128
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
    build_debpackage.sh \
    .github/* \
    .github/workflows/*

DISTFILES += \
    LICENSE.md \
    Authors.md \
    Authors_zh_CN.md \
    README_zh_CN.md \
    README.md \
    ChangeLog.md \
    ChangeLog_zh_CN.md

RESOURCES += \
    Src/Resource/ResourceTasks.qrc
