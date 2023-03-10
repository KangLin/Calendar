# 作者：康林 <kl222@126.com>

cmake_minimum_required(VERSION 2.8)

project(Calendar)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "verbose")

if(POLICY CMP0083)
    cmake_policy(SET CMP0083 NEW)
endif()

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT DEFINED CMAKE_BUILD_TYPE)
string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
if("debug" STREQUAL build_type)
    add_definitions(-D_DEBUG)
endif()

#需要的QT组件
SET(QT_COMPONENTS Core Gui Widgets Xml Network Multimedia Sql)
if(ANDROID)
    SET(QT_COMPONENTS ${QT_COMPONENTS} AndroidExtras)
endif()
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${QT_COMPONENTS})
message("QT_VERSION:${Qt${QT_VERSION_MAJOR}_VERSION}")
if(Qt${QT_VERSION_MAJOR}_VERSION VERSION_LESS 5.10.0 AND ANDROID)
    message(FATAL_ERROR "Qt must great 5.10.0")
endif()
if(Qt${QT_VERSION_MAJOR}_FOUND)
    FOREACH(_COMPONENT ${QT_COMPONENTS})
        SET(QT_LIBRARIES ${QT_LIBRARIES} Qt${QT_VERSION_MAJOR}::${_COMPONENT})
    ENDFOREACH()
endif()
get_filename_component(QT_INSTALL_DIR "${Qt${QT_VERSION_MAJOR}_DIR}/../../.." ABSOLUTE)
message("QT_INSTALL_DIR:${QT_INSTALL_DIR}")

#打开 qt 编译工具
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_VERBOSE_MAKEFILE ON)

IF(MSVC)
    # This option is to enable the /MP switch for Visual Studio 2005 and above compilers
    OPTION(WIN32_USE_MP "Set to ON to build with the /MP option (Visual Studio 2005 and above)." ON)
    MARK_AS_ADVANCED(WIN32_USE_MP)
    IF(WIN32_USE_MP)
        #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        add_compile_options(/MP)
    ENDIF(WIN32_USE_MP)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
ENDIF(MSVC)
SET(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs")
if (BUILD_SHARED_LIBS)
	add_definitions(-DBUILD_SHARED_LIBS)
    if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
       # Just setting CMAKE_POSITION_INDEPENDENT_CODE should be enough to set
       # -fPIC for GCC but sometimes it still doesn't get set, so make sure it
       # does.
       add_definitions("-fPIC")
    endif()
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckFunctionExists)
include(InstallRequiredSystemLibraries)

#CHECK_INCLUDE_FILE_CXX("string" HAVE_STRING_H)
#check_include_file("math.h" HAVE_MATH_H)

#check_function_exists("fabs" HAVE_FABS)

set(BUILD_PLATFORM "${CMAKE_SYSTEM_NAME}")

# ----------------------------------------------------------------------------
# Detect compiler and target platform architecture
# ----------------------------------------------------------------------------
if(NOT ANDROID)
    if(X86_64 OR CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(BUILD_ARCH x86_64)
    elseif(X86 OR CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(BUILD_ARCH x86)
    endif()
else()
    set(BUILD_ARCH ${CMAKE_ANDROID_ARCH_ABI})
endif()
message("CMAKE_SYSTEM_PROCESSOR:${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_ANDROID_ARCH_ABI:${CMAKE_ANDROID_ARCH_ABI}")
message("CMAKE_ANDROID_ARCH:${CMAKE_ANDROID_ARCH}")

if( "${RabbitCommon_DIR}" STREQUAL "" )
    set(RabbitCommon_DIR $ENV{RabbitCommon_DIR})
    if( "${RabbitCommon_DIR}" STREQUAL "" )
        set(RabbitCommon_DIR ${CMAKE_SOURCE_DIR}/../RabbitCommon)
    endif()
endif()

if(DEFINED RabbitCommon_DIR AND EXISTS ${RabbitCommon_DIR}/Src)
    add_subdirectory(${RabbitCommon_DIR}/Src ${CMAKE_BINARY_DIR}/RabbitCommon)
else()
    message("1. Please download RabbitCommon source code from https://github.com/KangLin/RabbitCommon")
    message("   ag:")
    message("       git clone https://github.com/KangLin/RabbitCommon.git")
    message("2. Then set cmake value or environment variable RabbitCommon_DIR to download root dirctory.")
    message("   ag:")
    message(FATAL_ERROR "       cmake -DRabbitCommon_DIR= ")
endif()

GET_VERSION(OUT_VERSION Calendar_VERSION
    OUT_REVISION Calendar_VERSION_REVISION)
message("Calendar_VERSION:${Calendar_VERSION}; Calendar_VERSION_REVISION:${Calendar_VERSION_REVISION}")
if(NOT Calendar_VERSION)
    set(Calendar_VERSION "v1.0.7")
endif()
set(VERSION ${Calendar_VERSION})
add_subdirectory(3th_libs/LunarCalendar/Src)
add_subdirectory(Src)
option(BUILD_APP "Set to ON to build applaction" ON)
if(BUILD_APP)
    add_subdirectory(App)
endif(BUILD_APP)

set(OTHER_FILES
    License.md
    Authors.md
    ChangeLog.md
    Authors_zh_CN.md
    ChangeLog_zh_CN.md)

# Create install runtime target
add_custom_target(install-runtime
  COMMAND
     "${CMAKE_COMMAND}" -DCMAKE_INSTALL_COMPONENT=Runtime 
     -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake"
)
# Create uninstall runtime target
add_custom_target(uninstall-runtime
  COMMAND
     "${CMAKE_COMMAND}" -DCMAKE_INSTALL_COMPONENT=Runtime 
     -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)
# Create will be delete files
CONFIGURE_FILE(
    "${RabbitCommon_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
# Create unistall target
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    DEPENDS uninstall-runtime)

if(ANDROID)
    # Install other files
    INSTALL(FILES ${OTHER_FILES} DESTINATION "assets" COMPONENT Runtime)
else()
    # Install other files
    INSTALL(FILES ${OTHER_FILES} DESTINATION "." COMPONENT Runtime)
endif()

if(WIN32)
    INSTALL(FILES Install/Install.nsi DESTINATION "${CMAKE_BINARY_DIR}"
        COMPONENT Runtime)
endif()

message("Build arch:${BUILD_ARCH}")
message("Build app:${BUILD_APP}")
message("Build shared library:${BUILD_SHARED_LIBS}")
