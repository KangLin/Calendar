#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T09:35:47
#
#-------------------------------------------------

TEMPLATE = subdirs
DESTDIR = $$OUT_PWD/bin

lib.subdir = Src
App.depends = lib
CONFIG *= ordered
SUBDIRS = lib App

isEmpty(PREFIX) {
    android {
        PREFIX = /.
    } else {
        PREFIX = $$OUT_PWD/install
    } 
}
other.files = License.md Authors.md ChangeLog.md Authors_zh_CN.md \
              ChangeLog_zh_CN.md App/AppIcon.ico
other.path = $$PREFIX
other.CONFIG += no_check_exist 

install.files = Install/Install.nsi
install.path = $$OUT_PWD
install.CONFIG += directory no_check_exist 
!android : INSTALLS += other
win32:  INSTALLS += install

OTHER_FILES += Install/* \
    appveyor.yml \
    ci/* \
    tag.sh \ 
    Update/* \
    CMakeLists.txt \
    etc/* \
    cmake/* \
    .travis.yml

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
    App/Resource/Resource.qrc 
   
