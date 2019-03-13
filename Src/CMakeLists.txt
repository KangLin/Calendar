set(HEAD_FILES
    Task.h
    Tasks.h
    TasksList.h
    TaskLockScreen.h
    TaskTrayIconPrompt.h
    FrmTop.h
    TaskPrompt.h
    FrmStickyNotes.h
    Global/GlobalDir.h
    Global/Log.h
    FrmFullScreen.h
    ObjectFactory.h
    Global/Tool.h
    FrmTaskPropery.h
    ViewTaskProperty.h
    FrmTasks.h 
    TaskPromptDelay.h
    FrmTasksList.h
    Sticky.h
    FrmStickyList.h
    StickyModel.h
    StickyItemDelegate.h)
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
    Global/Tool.cpp
    FrmTaskPropery.cpp
    ViewTaskProperty.cpp
    FrmTasks.cpp
    TaskPromptDelay.cpp
    FrmTasksList.cpp
    Sticky.cpp
    FrmStickyList.cpp
    StickyModel.cpp
    StickyItemDelegate.cpp)
set(SOURCE_UI_FILES
    FrmFullScreen.ui
    FrmTop.ui
    FrmStickyNotes.ui
    FrmTaskProperty.ui
    FrmTasks.ui
    FrmTasksList.ui
    FrmStickyList.ui)
#设置资源文件
SET(RCC_FILES
    Resource/Resource.qrc
    Resource/sink/dark/style.qrc
    )

if(WIN32)
    #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
endif()
add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEAD_FILES} ${SOURCE_UI_FILES} ${RCC_FILES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
GENERATE_EXPORT_HEADER(${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LOWER_PROJECT_NAME}_export.h DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# Install target
INSTALL(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        )
# Install head files
INSTALL(FILES ${HEAD_FILES} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
# Install cmake files
#configure_file(TransformCoordinateConfig.cmake.in ${CMAKE_BINARY_DIR}/TransformCoordinateConfig.cmake @ONLY)
#install(FILES ${CMAKE_BINARY_DIR}/TransformCoordinateConfig.cmake DESTINATION .)
#write_basic_package_version_file(
#    "${CMAKE_BINARY_DIR}/TransformCoordinateConfigVersion.cmake"
#    VERSION ${BUILD_VERSION}
#    COMPATIBILITY AnyNewerVersion)
#install(FILES ${CMAKE_BINARY_DIR}/TransformCoordinateConfigVersion.cmake DESTINATION .)
#if(NOT MSVC)
#    # Install pc files
#    configure_file(TransformCoordinate.pc.in ${CMAKE_BINARY_DIR}/TransformCoordinate.pc @ONLY)
#    install(FILES ${CMAKE_BINARY_DIR}/TransformCoordinate.pc DESTINATION lib/pkgconfig)
#endif()
IF(WIN32 AND BUILD_SHARED_LIBS)
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