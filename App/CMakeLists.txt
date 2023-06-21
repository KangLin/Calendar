project(CalendarApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "verbose")

set(HEAD_FILES
    MainWindow.h 
    DlgOption.h)
set(SOURCE_FILES
    main.cpp 
    MainWindow.cpp
    DlgOption.cpp)
set(SOURCE_UI_FILES
    MainWindow.ui
    DlgOption.ui)
if(WIN32)
    set(RCC_FILES AppIcon.rc)
endif()
LIST(APPEND PRIVATE_DEFINITIONS
    Calendar_REVISION="${Calendar_REVISION}"
    Calendar_VERSION="${Calendar_VERSION}"
    BUILD_ARCH="${BUILD_ARCH}"
    BUILD_PLATFORM="${BUILD_PLATFORM}")

ADD_TARGET(NAME ${PROJECT_NAME}
    ISEXE
    ISWINDOWS
    SOURCE_FILES ${SOURCE_FILES} ${HEAD_FILES} ${SOURCE_UI_FILES} ${RCC_FILES}
    PRIVATE_DEFINITIONS RABBITCOMMON ${PRIVATE_DEFINITIONS}
    PRIVATE_LIBS Tasks ${QT_LIBRARIES} RabbitCommon
    VERSION ${Calendar_VERSION})

find_package(OpenSSL)
IF(OpenSSL_FOUND)
    if(ANDROID)
        set_property(TARGET ${PROJECT_NAME}
            APPEND PROPERTY QT_ANDROID_EXTRA_LIBS
            $<TARGET_FILE:OpenSSL::SSL>
            $<TARGET_FILE:OpenSSL::Crypto>)
    endif()
    if(WIN32)
        INSTALL_TARGETS(TARGETS OpenSSL::SSL OpenSSL::Crypto)
    endif()
else()
    message(AUTHOR_WARNING "Don't find openssl")
ENDIF()

if(WIN32)
    INSTALL(FILES AppIcon.ico DESTINATION "." COMPONENT Runtime)
endif()

if(NOT ANDROID AND UNIX)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/share/org.Rabbit.Calendar.desktop
        DESTINATION "share/applications" COMPONENT Runtime)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Src/Resource/image/Calendar.png
        DESTINATION "share/pixmaps" COMPONENT Runtime)
    INSTALL(PROGRAMS ${CMAKE_SOURCE_DIR}/share/Calendar.sh
        DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime)
endif()

if(Log4Qt_FOUND)
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/etc/Calendar_log4qt.conf)
        configure_file(${CMAKE_SOURCE_DIR}/etc/Calendar_log4qt.conf
            ${CMAKE_BINARY_DIR}/etc/Calendar_log4qt.conf
            COPYONLY)
    endif()
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/etc/Calendar_log4qt.conf
        DESTINATION etc COMPONENT Runtime)
else()
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/etc/Calendar_logqt.conf)
        configure_file(${CMAKE_SOURCE_DIR}/etc/Calendar_logqt.conf
            ${CMAKE_BINARY_DIR}/etc/Calendar_logqt.conf
            COPYONLY)
    endif()
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/etc/Calendar_logqt.conf
        DESTINATION etc COMPONENT Runtime)
endif()

set(OTHER_FILES
    ${CMAKE_SOURCE_DIR}/License.md
    ${CMAKE_SOURCE_DIR}/Authors.md
    ${CMAKE_SOURCE_DIR}/ChangeLog.md
    ${CMAKE_SOURCE_DIR}/Authors_zh_CN.md
    ${CMAKE_SOURCE_DIR}/ChangeLog_zh_CN.md)

# Install other files
INSTALL_FILE(SOURCES ${OTHER_FILES} DESTINATION "." COMPONENT Runtime)
