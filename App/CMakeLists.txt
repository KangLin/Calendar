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
    PRIVATE_LIBS RabbitCommon LunarCalendar Tasks ${QT_LIBRARIES}
    VERSION ${Calendar_VERSION})

if(NOT ANDROID AND (UNIX OR IOS))
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/share/org.Rabbit.Calendar.desktop
        DESTINATION "share/applications"
            COMPONENT Application)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Src/Resource/image/Calendar.png
        DESTINATION "share/pixmaps"
            COMPONENT Application)
    INSTALL(PROGRAMS ${CMAKE_SOURCE_DIR}/share/Calendar.sh
        DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT Application)
endif()

if(NOT EXISTS ${CMAKE_BINARY_DIR}/etc/Calendar_logqt.ini)
    configure_file(${CMAKE_SOURCE_DIR}/etc/Calendar_logqt.ini
        ${CMAKE_BINARY_DIR}/etc/Calendar_logqt.ini
        COPYONLY)
endif()
INSTALL(FILES ${CMAKE_SOURCE_DIR}/etc/Calendar_logqt.ini
    DESTINATION etc COMPONENT Application)

set(OTHER_FILES
    ${CMAKE_SOURCE_DIR}/License.md
    ${CMAKE_SOURCE_DIR}/Authors.md
    ${CMAKE_SOURCE_DIR}/ChangeLog.md
    ${CMAKE_SOURCE_DIR}/Authors_zh_CN.md
    ${CMAKE_SOURCE_DIR}/ChangeLog_zh_CN.md)

# Install other files
INSTALL_FILE(SOURCES ${OTHER_FILES}
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
        COMPONENT Application)

if(WIN32)
    # 替换 Install.nsi 中的 CMAKE_INSTALL_PREFIX 等
    configure_file(${CMAKE_SOURCE_DIR}/Install/Install.nsi
        ${CMAKE_BINARY_DIR}/Install.nsi @ONLY)
    INSTALL(FILES AppIcon.ico DESTINATION "." COMPONENT Application)
endif()
