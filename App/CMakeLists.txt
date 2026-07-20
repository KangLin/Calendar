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

set(APP_ID io.github.KangLin.Calendar)
if(ANDROID)
    if(NOT Calendar_VERSION)
        message(WARNING "Calendar_VERSION is empty, using default version")
        set(Calendar_VERSION "1.0.0")
    endif()

    # 确保版本号格式正确
    if(NOT Calendar_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+")
        message(WARNING "Version format is not 'x.y.z', using fallback parsing")
    endif()

    # 使用方案一的解析逻辑
    string(REGEX MATCHALL "[0-9]+" VERSION_PARTS "${Calendar_VERSION}")
    list(LENGTH VERSION_PARTS PARTS_COUNT)

    if(PARTS_COUNT GREATER_EQUAL 3)
        list(GET VERSION_PARTS 0 VERSION_MAJOR)
        list(GET VERSION_PARTS 1 VERSION_MINOR)
        list(GET VERSION_PARTS 2 VERSION_PATCH)
    else()
        # 不足3段时补齐
        set(VERSION_MAJOR 1)
        set(VERSION_MINOR 0)
        set(VERSION_PATCH 0)
    endif()

    math(EXPR QT_ANDROID_VERSION_CODE "${VERSION_MAJOR}*10000 + ${VERSION_MINOR}*100 + ${VERSION_PATCH}")
    set(QT_ANDROID_VERSION_NAME "${Calendar_VERSION}")

    message(STATUS "${PROJECT_NAME} Version Code: ${QT_ANDROID_VERSION_CODE}, Version Name: ${QT_ANDROID_VERSION_NAME}")

    set_target_properties(${PROJECT_NAME} PROPERTIES
        QT_ANDROID_PACKAGE_NAME "${APP_ID}"
        QT_ANDROID_APP_NAME "@string/app_name"
        QT_ANDROID_APP_ICON "@drawable/icon"
        QT_ANDROID_VERSION_CODE ${QT_ANDROID_VERSION_CODE}
        QT_ANDROID_VERSION_NAME ${QT_ANDROID_VERSION_NAME}
        #QT_ANDROID_MIN_SDK_VERSION 28
        QT_ANDROID_TARGET_SDK_VERSION 34
        )
    qt_add_android_permission(${PROJECT_NAME}
        NAME android.permission.WRITE_EXTERNAL_STORAGE
    )
    qt_add_android_permission(${PROJECT_NAME}
        NAME android.permission.READ_EXTERNAL_STORAGE
    )
elseif(UNIX)
    configure_file(${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_DATADIR}/applications/${APP_ID}.desktop.in
        ${CMAKE_BINARY_DIR}/${APP_ID}.desktop)
    INSTALL(FILES ${CMAKE_BINARY_DIR}/${APP_ID}.desktop
        DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
            COMPONENT Application)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Src/Resource/image/Calendar.png
        DESTINATION "${CMAKE_INSTALL_DATADIR}/pixmaps"
            COMPONENT Application
        RENAME ${APP_ID}.png)
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
