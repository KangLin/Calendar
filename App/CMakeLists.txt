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

#翻译
GENERATED_QT_TRANSLATIONS(
    SOURCES ${SOURCE_FILES} ${HEAD_FILES} ${SOURCE_UI_FILES}
    OUT_QRC TRANSLATIONS_QRC_FILES
    )
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
if(BUILD_TYPE STREQUAL "debug")
    LIST(APPEND PRIVATE_DEFINITIONS DEBUG)
    LIST(APPEND RCC_FILES
        ${TRANSLATIONS_QRC_FILES}
        )
endif()

add_definitions(-DCalendar_VERSION="${Calendar_VERSION}")
add_definitions(-DBUILD_ARCH="${BUILD_ARCH}")
add_definitions(-DBUILD_PLATFORM="${BUILD_PLATFORM}")

if(ANDROID)
    add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEAD_FILES} ${SOURCE_UI_FILES} ${RCC_FILES})
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEAD_FILES} ${SOURCE_UI_FILES} AppIcon.rc ${RCC_FILES})
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PRIVATE_DEFINITIONS})
SET(APP_LIBS Tasks ${QT_LIBRARIES})
if(TARGET RabbitCommon)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DRABBITCOMMON)
    target_include_directories(${PROJECT_NAME}
        PRIVATE "${RabbitCommon_DIR}/Src" "${RabbitCommon_DIR}/Src/export")
    set(APP_LIBS ${APP_LIBS} RabbitCommon)
endif()
target_link_libraries(${PROJECT_NAME} ${APP_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Src" "${CMAKE_BINARY_DIR}")
if(MINGW)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "-mwindows")
elseif(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE
        "/SUBSYSTEM:WINDOWS\",5.01\" /ENTRY:mainCRTStartup")
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    VERSION ${Calendar_VERSION})
if(UNIX AND NOT ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${PROJECT_NAME})
endif()

# Install target
if(ANDROID)
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "libs/${ANDROID_ABI}"
            COMPONENT Runtime
        LIBRARY DESTINATION "libs/${ANDROID_ABI}"
            COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
elseif(WIN32)
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT Runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
else()
    INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            COMPONENT Runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            COMPONENT Runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
endif()

if(WIN32)
    INSTALL(FILES AppIcon.ico DESTINATION "." COMPONENT Runtime)
endif()

if(UNIX)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/debian/Calendar.desktop
        DESTINATION "share/applications" COMPONENT Runtime)
    INSTALL(FILES ${CMAKE_SOURCE_DIR}/Src/Resource/image/Calendar.png
        DESTINATION "share/pixmaps" COMPONENT Runtime)
endif()

IF("Release" STREQUAL CMAKE_BUILD_TYPE AND WIN32)
    SET(RUNTIME_FILE "${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}")
    IF(CMAKE_BUILD_TYPE MATCHES Release AND MINGW)
        #windeployqt 分发时，是根据是否 strip 来判断是否是 DEBUG 版本,而用mingw编译时,qt没有自动 strip
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND strip "$<TARGET_FILE:${PROJECT_NAME}>"
            )
    ENDIF()

    #注意 需要把 ${QT_INSTALL_DIR}/bin 加到环境变量PATH中  
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${QT_INSTALL_DIR}/bin/windeployqt"
        --compiler-runtime
        --verbose 7
        "$<TARGET_FILE:${PROJECT_NAME}>"
        )
    INSTALL(DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT Runtime)
ENDIF()

IF(ANDROID)
    Set(JSON_FILE ${CMAKE_CURRENT_BINARY_DIR}/android-libCalendarApp.so-deployment-settings.json)
    GENERATED_DEPLOYMENT_SETTINGS(NAME ${JSON_FILE}
        APPLACTION "${CMAKE_BINARY_DIR}/bin/lib${PROJECT_NAME}.so")

    add_custom_target(APK #TARGET ${PROJECT_NAME} POST_BUILD
        #COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" ${CMAKE_INSTALL_PREFIX}/libs/${ANDROID_ABI}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
        #COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/libs/${ANDROID_ABI}
        #COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE_DIR:${PROJECT_NAME}>/*" ${CMAKE_INSTALL_PREFIX}/libs/${ANDROID_ABI}
        #注意 需要把 ${QT_INSTALL_DIR}/bin 加到环境变量PATH中
        COMMAND "${QT_INSTALL_DIR}/bin/androiddeployqt"
            --output ${CMAKE_INSTALL_PREFIX}
            --input ${JSON_FILE}
            --verbose
            --gradle
            --android-platform ${ANDROID_PLATFORM}
        )
ENDIF(ANDROID)
