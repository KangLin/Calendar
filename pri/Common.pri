#Get app version use git, please set git path to environment variable PATH
isEmpty(Calendar_VERSION) {
    isEmpty(GIT) : GIT=$$(GIT)
    isEmpty(GIT) : GIT=git
    isEmpty(GIT_DESCRIBE) {
        GIT_DESCRIBE = $$system(cd $$system_path($$_PRO_FILE_PWD_) && $$GIT describe --tags)
        isEmpty(Calendar_VERSION) {
            Calendar_VERSION = $$GIT_DESCRIBE
        }
    }
    Calendar_VERSION_REVISION = $$system(cd $$system_path($$_PRO_FILE_PWD_) && $$GIT rev-parse --short HEAD)
    isEmpty(Calendar_VERSION) {
        Calendar_VERSION = $$Calendar_VERSION_REVISION
    }
    
    isEmpty(Calendar_VERSION){
        warning("Built without git, please add Calendar_VERSION to DEFINES or add git path to environment variable GIT or qmake parameter GIT")
    }
}
isEmpty(Calendar_VERSION){
    Calendar_VERSION="v1.0.7"
}
message("Calendar Calendar_VERSION:$$Calendar_VERSION")
DEFINES += Calendar_VERSION=\"\\\"$$quote($$Calendar_VERSION)\\\"\"
DEFINES += Calendar_VERSION_REVISION=\"\\\"$$quote($$Calendar_VERSION_REVISION)\\\"\"
VERSION=$$replace(Calendar_VERSION, v,)
win32{
    VERSION=$$split(VERSION, -)
    VERSION=$$first(VERSION)
}

android{
    DEFINES += BUILD_ARCH=\"\\\"$${ANDROID_TARGET_ARCH}\\\"\"
} else {
    contains(QMAKE_TARGET.arch, x86_64) {
        DEFINES += BUILD_ARCH=\"\\\"x86_64\\\"\"
    } else {
        DEFINES += BUILD_ARCH=\"\\\"x86\\\"\"
    }
}
CONFIG(debug, debug|release) : DEFINES += _DEBUG
DEFINES += BUILD_PLATFORM=\"\\\"$${QMAKE_PLATFORM}\\\"\"

isEmpty(PREFIX) {
    android {
        PREFIX = /
    } else {
        PREFIX = $$OUT_PWD/../install
    } 
}

#Support windows xp
msvc : QMAKE_LFLAGS *= /SUBSYSTEM:WINDOWS",5.01" 
mingw : DEFINES += "_WIN32_WINNT=0x0501" 
