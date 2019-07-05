#Get app version use git, please set git path to environment variable PATH
isEmpty(BUILD_VERSION) {
    isEmpty(GIT) : GIT=$$(GIT)
    isEmpty(GIT) : GIT=git
    isEmpty(GIT_DESCRIBE) {
        GIT_DESCRIBE = $$system(cd $$system_path($$_PRO_FILE_PWD_) && $$GIT describe --tags)
        isEmpty(BUILD_VERSION) {
            BUILD_VERSION = $$GIT_DESCRIBE
        }
    }
    isEmpty(BUILD_VERSION) {
        BUILD_VERSION = $$system(cd $$system_path($$_PRO_FILE_PWD_) && $$GIT rev-parse --short HEAD)
    }
    
    isEmpty(BUILD_VERSION){
        warning("Built without git, please add BUILD_VERSION to DEFINES or add git path to environment variable GIT or qmake parameter GIT")
    }
}
isEmpty(BUILD_VERSION){
    BUILD_VERSION="v0.1.7"
}
message("Tasks BUILD_VERSION:$$BUILD_VERSION")
DEFINES += BUILD_VERSION=\"\\\"$$quote($$BUILD_VERSION)\\\"\"
VERSION=$$replace(BUILD_VERSION, v,)
win32{
    VERSION=$$split(VERSION, -)
    VERSION=$$first(VERSION)
}

contains(QMAKE_TARGET.arch, x86_64) {
    DEFINES += BUILD_ARCH=\"\\\"x86_64\\\"\"
} else {
    DEFINES += BUILD_ARCH=\"\\\"x86\\\"\"
}
CONFIG(debug, debug|release) : DEFINES += _DEBUG
DEFINES += BUILD_PLATFORM=\"\\\"$${QMAKE_PLATFORM}\\\"\"

isEmpty(PREFIX) {
    android {
        PREFIX = /.
    } else {
        PREFIX = $$OUT_PWD/../install
    } 
}

#Support windows xp
msvc : QMAKE_LFLAGS *= /SUBSYSTEM:WINDOWS",5.01" 
mingw : DEFINES += "_WIN32_WINNT=0x0501" 
