project(Tasks LANGUAGES CXX)

set(INSTALLHEADER_FILES
    FrmTasksList.h
    FrmStickyList.h
    FrmTasksList.h
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
    FrmTopActivity.h
    DlgContainer.h
    FrmCustomActivity.h
    ThreadTasks.h
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
    DlgTaskActivity.cpp
    FrmTopActivity.cpp
    DlgContainer.cpp
    FrmCustomActivity.cpp
    ThreadTasks.cpp
    )
set(SOURCE_UI_FILES
    FrmFullScreen.ui
    FrmTop.ui
    FrmStickyNotes.ui
    FrmTaskProperty.ui
    FrmTasks.ui
    FrmTasksList.ui
    FrmStickyList.ui
    DlgTaskActivity.ui
    DlgContainer.ui
    FrmCustomActivity.ui
    )

#设置资源文件
SET(RCC_FILES
    Resource/ResourceTasks.qrc
    )

if(Calendar_VERSION)
    list(APPEND Tasks_DEFINITIONS
        Calendar_VERSION="${Calendar_VERSION}"
        Calendar_REVISION="${Calendar_REVISION}"
        )
endif()

include(GenerateExportHeader)
ADD_TARGET(NAME ${PROJECT_NAME}
    SOURCE_FILES ${SOURCE_FILES} ${HEAD_FILES}
        ${SOURCE_UI_FILES} ${RCC_FILES}
    DEFINITIONS ${Tasks_DEFINITIONS}
    INCLUDE_DIRS
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> # See: http://www.it1352.com/478094.html
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE_LIBS LunarCalendar RabbitCommon ${QT_LIBRARIES}
    PRIVATE_INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_BINARY_DIR}
        ${RabbitCommon_DIR}/Src
        ${RabbitCommon_DIR}/Src/export
    INSTALL_HEADER_FILES "${INSTALLHEADER_FILES}"
    VERSION ${Calendar_VERSION}
    )

foreach(d ${Tasks_DEFINITIONS})
    SET(Tasks_DEFINITIONS_PC "${Tasks_DEFINITIONS_PC} -D${d}")
endforeach()
# Install pc files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Tasks.pc.in
    ${CMAKE_BINARY_DIR}/Tasks.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/Tasks.pc
    DESTINATION lib/pkgconfig)

# Install xml files
if(ANDROID)
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/etc/
        DESTINATION "assets/etc/xml" COMPONENT Runtime)
else()
    INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/etc/
        DESTINATION "etc/xml" COMPONENT Runtime)
endif()

INSTALL_ICON_THEME()
