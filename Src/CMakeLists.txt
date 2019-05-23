project(Tasks)

set(INSTALLHEADER_FILES
    FrmTasksList.h
    FrmStickyList.h
    FrmTasksList.h    
    Global/GlobalDir.h
    Global/TasksTools.h
    )
set(HEAD_FILES
    ${INSTALLHEADER_FILES}
    Task.h
    Tasks.h
    TasksList.h
    TaskLockScreen.h
    TaskTrayIconPrompt.h
    FrmTop.h
    TaskPrompt.h
    FrmStickyNotes.h
    Global/Log.h
    FrmFullScreen.h
    ObjectFactory.h
    FrmTaskPropery.h
    ViewTaskProperty.h
    FrmTasks.h 
    TaskPromptDelay.h
    Sticky.h   
    StickyModel.h
    StickyItemDelegate.h
    FrmTasksList.h
    TaskActivity.h
    DlgTaskActivity.h
    )
set(SOURCE_FILES
    Task.cpp
    Tasks.cpp
    TasksList.cpp
    TaskLockScreen.cpp
    TaskTrayIconPrompt.cpp
    FrmTop.cpp
    TaskPrompt.cpp
    FrmStickyNotes.cpp
    Global/GlobalDir.cpp
    Global/Log.cpp
    FrmFullScreen.cpp
    Global/TasksTools.cpp
    FrmTaskPropery.cpp
    ViewTaskProperty.cpp
    FrmTasks.cpp
    TaskPromptDelay.cpp
    FrmTasksList.cpp
    Sticky.cpp
    FrmStickyList.cpp
    StickyModel.cpp
    StickyItemDelegate.cpp
    FrmCalendar.cpp
    TaskActivity.cpp
    DlgTaskActivity.cpp)
set(SOURCE_UI_FILES
    FrmFullScreen.ui
    FrmTop.ui
    FrmStickyNotes.ui
    FrmTaskProperty.ui
    FrmTasks.ui
    FrmTasksList.ui
    FrmStickyList.ui
    FrmCalendar.ui
    DlgTaskActivity.ui)

#翻译
include(${CMAKE_SOURCE_DIR}/cmake/Qt5CorePatches.cmake) 
include(${CMAKE_SOURCE_DIR}/cmake/Translations.cmake)

#设置资源文件
SET(RCC_FILES
    Resource/ResourceTasks.qrc
    Resource/sink/dark/style.qrc
    ${TRANSLATIONS_RESOURCE_FILES}
    )

if(WIN32)
    #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
endif()
add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEAD_FILES}
    ${SOURCE_UI_FILES} ${RCC_FILES})
add_dependencies(${TRANSLATIONS_NAME} translations_${TRANSLATIONS_NAME})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} LunarCalendar)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../3th_libs/LunarCalendar/Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../3th_libs/LunarCalendar/Src/export)
GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
set(INSTALLHEADER_FILES ${INSTALLHEADER_FILES} 
    ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h)
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h
    DESTINATION ${CMAKE_BINARY_DIR})
# Install head files
#INSTALL(FILES ${HEAD_FILES} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
set_property(
    TARGET
        ${PROJECT_NAME}
    PROPERTY
        PUBLIC_HEADER "${INSTALLHEADER_FILES}"
)

export(
    TARGETS
        ${PROJECT_NAME}
    FILE
        ${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}.cmake  # not going to be installed
)

# Install target
INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Tasks
        )

INSTALL(
        EXPORT ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
       )

# Install cmake files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/TasksConfig.cmake.in ${CMAKE_BINARY_DIR}/TasksConfig.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/TasksConfig.cmake DESTINATION .)
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/TasksConfigVersion.cmake"
    VERSION ${BUILD_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_BINARY_DIR}/TasksConfigVersion.cmake DESTINATION .)
if(NOT MSVC)
    # Install pc files
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Tasks.pc.in ${CMAKE_BINARY_DIR}/Tasks.pc @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/Tasks.pc DESTINATION lib/pkgconfig)
endif()

IF("Release" STREQUAL CMAKE_BUILD_TYPE AND WIN32 AND BUILD_SHARED_LIBS)
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
    #INSTALL(DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>/" DESTINATION "${CMAKE_INSTALL_BINDIR}")
ENDIF()
