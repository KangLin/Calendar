## [<img src="App/AppIcon.ico" title="日历" width="16" height="16"/>日历](https://github.com/KangLin/Calendar)

作者：康 林 <kl222@126.com>

------------------------------------------------

[:us: 英语](README.md)

[![build](https://github.com/KangLin/Calendar/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/KangLin/Calendar/actions/workflows/build.yml)
[![build](https://github.com/KangLin/Calendar/actions/workflows/build.yml/badge.svg?branch=develop)](https://github.com/KangLin/Calendar/actions/workflows/build.yml)
[![Appveyor build status](https://ci.appveyor.com/api/projects/status/hw8wsnwinrnohhda?svg=true)](https://ci.appveyor.com/project/KangLin/Calendar)

[![GitHub issues](https://img.shields.io/github/issues/KangLin/Calendar)](https://github.com/KangLin/Calendar/issues)

[![GitHub 点赞量](https://img.shields.io/github/stars/KangLin/Calendar?label=Github%20点赞量)](https://star-history.com/#KangLin/Calendar&Date)
[![Gitee 点赞量](https://gitee.com/kl222/Calendar/badge/star.svg?theme=dark)](https://gitee.com/kl222/Calendar/stargazers)

[![github 最后发行版本下载](https://img.shields.io/github/release/KangLin/Calendar.svg?label=Github%20最后发行版本下载)](https://github.com/KangLin/Calendar/releases/latest)
[![sourceforge 最后发行版本下载](https://a.fsdn.com/con/app/sf-download-button)](https://sourceforge.net/projects/rabbitcalendar/files/latest/download)

[![github 下载量](https://img.shields.io/github/downloads/KangLin/Calendar/total?label=Github%20下载量)](https://github.com/KangLin/Calendar/releases)
[![Download Calendar](https://img.shields.io/sourceforge/dt/rabbitcalendar.svg?label=Sourceforge%20下载量)](https://sourceforge.net/projects/rabbitcalendar/files/latest/download)

------------------------------------------------

* [功能](#功能)
* [屏幕截图](#屏幕截图)
* [捐赠](#捐赠)
* [下载](#下载)
* [依赖](#依赖)
* [编译](#编译)
* [使用](#使用)
* [贡献](#贡献)
* [许可协议](#许可协议)


### 项目位置
- 代码库:
  + 主库: https://github.com/KangLin/Calendar
  + 镜像库:
    - https://gitee.com/kl222/Calendar
    - https://gitlab.com/kl222/Calendar
    - https://sourceforge.net/projects/rabbitcalendar/
    - https://invent.kde.org/kanglin/Calendar
- [项目主页](https://kanglin.github.io/Calendar/)

### 功能

- [x] 日历
    - [x] 生日提醒（年周期提醒）,包括农历
    - [x] 月周期提醒
    - [x] 周周期提醒
    - [x] 自定义周期
- [x] 自定义任务
  - [x] 眼睛护士: 保护视力
- [x] 便签
- 跨平台，支持多操作系统
  + [x] Windows
  + [x] Linux、Unix
  + [x] Android
  + [x] Mac os
  + [ ] IOS

    Mac os 和 IOS ，本人没有相应设备，请有相应设备的同学自己编译，测试。

  详见：[Qt5 支持平台](https://doc.qt.io/qt-5/supported-platforms.html)、[Qt6 支持平台](https://doc.qt.io/qt-6/supported-platforms.html)。

### 屏幕截图

+ Unix 下截图
  - ![Calendar](Resource/Image/ScreenShot/Calendar_zh_CN.png)
  - ![Sticky](Resource/Image/ScreenShot/Sticky_zh_CN.png)
  - ![Tasks](Resource/Image/ScreenShot/Task_zh_CN.png)
+ Android 下截图
  - ![Android Calendar](Resource/Image/ScreenShot/AndroidCalendar_zh_CN.png)
  - ![Android Stricky List](Resource/Image/ScreenShot/AndroidStrickyList_zh_CN.png)
  - ![Android Stricky](Resource/Image/ScreenShot/AndroidStricky_zh_CN.png)
  - ![Android Tasks](Resource/Image/ScreenShot/AndroidTask_zh_CN.png)

### 捐赠
本软件如果对你有用，或者你喜欢它，请你捐赠，支持作者。谢谢！

[![捐赠](https://gitee.com/kl222/RabbitCommon/raw/master/Src/Resource/image/Contribute_zh_CN.png "捐赠")](https://gitee.com/kl222/RabbitCommon/raw/master/Src/Resource/image/Contribute_zh_CN.png "捐赠") 

### 下载

- [![最后发行版本下载](https://img.shields.io/github/release/KangLin/Calendar.svg?label=Github%20最后发行版本下载)](https://github.com/KangLin/Calendar/releases/latest)
- [![最后发行版本下载](https://a.fsdn.com/con/app/sf-download-button)](https://sourceforge.net/projects/rabbitcalendar/files/latest/download)

### 依赖
- [Qt (LGPL v2.1)](http://qt.io/)
  - Qt 官方发行版本： https://download.qt.io/official_releases/qt/
    - 则需要设置环境变量（或者 CMAKE 参数）：
      - QT_ROOT
      - Qt6：Qt6_ROOT 或者 Qt6_DIR 。
        详见：https://doc.qt.io/qt-6/cmake-get-started.html
      - Qt5：Qt5_ROOT 或者 Qt5_DIR 。
        详见：https://doc.qt.io/qt-5/cmake-get-started.html
      - 环境变量

            export QT_ROOT=Qt 安装位置
            # 编译 AppImage 需要
            export QMAKE=$QT_ROOT/bin/qmake

            # 当使用 Qt6 时
            export Qt6_ROOT=$QT_ROOT
            # 当使用 Qt5 时
            export Qt5_ROOT=$QT_ROOT

            # 或者
            # 当使用 Qt6 时
            export Qt6_DIR=$QT_ROOT/lib/cmake/Qt6
            # 当使用 Qt5 时
            export Qt5_DIR=$QT_ROOT/lib/cmake/Qt5

      - CMAKE 参数

            #当使用 Qt6 时
            cmake -DQT_ROOT=[Qt 安装位置] -DQt6_DIR=[Qt 安装位置] ......
            #当使用 Qt5 时
            cmake -DQT_ROOT=[Qt 安装位置] -DQt5_DIR=[Qt 安装位置] ......
            # 编译 AppImage 需要
            export QMAKE=$QT_ROOT/bin/qmake

  - 系统自带：
    - Qt5:

          ~$ sudo apt install qttools5-dev qttools5-dev-tools qtbase5-dev qtbase5-dev-tools qtmultimedia5-dev qtlocation5-dev libqt5svg5-dev

    - Qt6: 详见： [Script/build_depend.sh](../../Script/build_depend.sh)

          ~$ sudo apt install qmake6 qt6-tools-dev qt6-tools-dev-tools qt6-base-dev qt6-base-dev-tools qt6-qpa-plugins libqt6svg6-dev qt6-l10n-tools qt6-translations-l10n qt6-scxml-dev qt6-multimedia-dev

    - 系统安装多个分发版本 Qt 时。例如：同时安装 Qt5 和 Qt6 。
      系统使用 qtchooser 工具来选择当前的 Qt 版本。
  
          l@l:/home/RabbitRemoteControl$ qtchooser 
          Usage:
            qtchooser { -l | -list-versions | -print-env }
            qtchooser -install [-f] [-local] <name> <path-to-qmake>
            qtchooser -run-tool=<tool name> [-qt=<Qt version>] [program arguments]
            <executable name> [-qt=<Qt version>] [program arguments]

          Environment variables accepted:
           QTCHOOSER_RUNTOOL  name of the tool to be run (same as the -run-tool argument)
           QT_SELECT          version of Qt to be run (same as the -qt argument)
  
      - 查看当前系统安装的 Qt 版本

            l@l:/home/RabbitRemoteControl$ qtchooser -l
            4
            5
            default
            qt4-x86_64-linux-gnu
            qt4
            qt5-x86_64-linux-gnu
            qt5
            qt6

            # 查看当前环境的 Qt 版本
            l@l:/home/RabbitRemoteControl$ qtchooser --print-env
            QT_SELECT="default"
            QTTOOLDIR="[Paths]"
            QTLIBDIR="Prefix=/usr"
    
      - 设置当前环境的 Qt 版本

            export QT_SELECT=qt6  #设置当前环境 Qt 版本为 6

            # 查看当前环境的 Qt 版本
            l@l:/home/RabbitRemoteControl$ qtchooser --print-env
            QT_SELECT="qt6"
            QTTOOLDIR="/usr/lib/qt6/bin"
            QTLIBDIR="/usr/lib/aarch64-linux-gnu"
  
- [RabbitCommon](https://github.com/KangLin/RabbitCommon)
  
        git clone https://github.com/KangLin/RabbitCommon.git
        
- [LunarCalendar](https://github.com/KangLin/LunarCalendar)

### 编译
- 建立并进入build目录

        git clone --recursive https://github.com/KangLin/Calendar.git
        mkdir build

- 编译
  + CMAKE 参数：
    + Qt
      + QT_ROOT: Qt 安装位置
      + Qt6: 详见：https://doc.qt.io/qt-6/cmake-get-started.html
        + Qt6_ROOT: 与 QT_ROOT 相同
        + Qt6_DIR: $QT_ROOT/lib/cmake/Qt6
      + Qt5: 详见：https://doc.qt.io/qt-6/cmake-get-started.html
        + Qt5_ROOT: 与 QT_ROOT 相同
        + Qt5_DIR: $QT_ROOT/lib/cmake/Qt5
    + [必选] RabbitCommon_ROOT: 指向 RabbitCommon 源码目录
    + [可选] CMAKE_INSTALL_PREFIX: 安装前缀
  + windows 或 linux
  
        cd build
        cmake .. -DCMAKE_INSTALL_PREFIX=`pwd`/install \
               -DCMAKE_BUILD_TYPE=Release \
               -DQt5_DIR=${QT_ROOT}/lib/cmake/Qt5 \
               -DRabbitCommon_ROOT=
        cmake --build . --config Release --target install
        
  + android：
    Qt 版本必须大于等于 6  
    - 主机是linux
      + 编译

            cd build
            cmake .. -DCMAKE_BUILD_TYPE=Release \
               -DCMAKE_INSTALL_PREFIX=`pwd`/android-build \
               -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake \
               -DANDROID_ABI="armeabi-v7a with NEON" \
               -DANDROID_PLATFORM=android-18 \
               -DQt6_DIR= \
               -DRabbitCommon_ROOT= 
            cmake --build . --config Release

    　+ 安装
        - 安装库和程序

              cmake --build . --config Release --target install

    - 主机是windows
      + 编译

            cd build
            cmake .. -DCMAKE_INSTALL_PREFIX=%cd%\android-build ^
                -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ^
                -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%/build/cmake/android.toolchain.cmake ^
                -DCMAKE_MAKE_PROGRAM=%ANDROID_NDK%/prebuilt/windows-x86_64/bin/make.exe ^
                -DANDROID_ABI=arm64-v8a ^
                -DANDROID_ARM_NEON=ON ^
                -DANDROID_PLATFORM=android-24 ^
                -DQt6_DIR= ^
                -DRabbitCommon_ROOT= 

      + 安装
        - 安装库和程序

            cmake --build . --config Release --target install

    - 参数说明：https://developer.android.google.cn/ndk/guides/cmake
      + ANDROID_ABI: 可取下列值：
        目标 ABI。如果未指定目标 ABI，则 CMake 默认使用 armeabi-v7a。  
        有效的目标名称为：
        - armeabi：带软件浮点运算并基于 ARMv5TE 的 CPU。
        - armeabi-v7a：带硬件 FPU 指令 (VFPv3_D16) 并基于 ARMv7 的设备。
        - armeabi-v7a with NEON：与 armeabi-v7a 相同，但启用 NEON 浮点指令。这相当于设置 -DANDROID_ABI=armeabi-v7a 和 -DANDROID_ARM_NEON=ON。
        - arm64-v8a：ARMv8 AArch64 指令集。
        - x86：IA-32 指令集。
        - x86_64 - 用于 x86-64 架构的指令集。
      + ANDROID_NDK <path> 主机上安装的 NDK 根目录的绝对路径
      + ANDROID_PLATFORM: 如需平台名称和对应 Android 系统映像的完整列表，请参阅 [Android NDK 原生 API](https://developer.android.google.cn/ndk/guides/stable_apis.html)
      + ANDROID_ARM_MODE
      + ANDROID_ARM_NEON
      + ANDROID_STL: 指定 CMake 应使用的 STL
        - c++_shared: 使用 libc++ 动态库
        - c++_static: 使用 libc++ 静态库
        - none: 没有 C++ 库支持
        - system: 用系统的 STL

    - 安装 apk 到设备

           adb install android-build-debug.apk

- 安装注意  
Qt因为版权原因，没有提供openssl动态库，所以必须自己复制openssl的动态库到安装目录下。
    + windows
        - 如果是32的，可以在Qt安装程序Tools\QtCreator\bin目录下，找到openssl的动态库（libeay32.dll、ssleay32.dll）
        - 如果是64位，则需要自己下载openssl的二进制安装包。
    + linux

        sudo apt-get install libssl1.1

### 使用
- 直接用源码
  + 是QT工程
    - 库方式:
    在项目文件中加入下列语句：

            isEmpty(Calendar_DIR): Calendar_DIR=$ENV{Calendar_DIR}
            isEmpty(Calendar_DIR){
                message("1. Please download Calendar source code from https://github.com/KangLin/Calendar")
                message("   ag:")
                message("       git clone https://github.com/KangLin/Calendar.git")
                message("2. Build the project, get library")
                error("2. Then set value Calendar_DIR to library root directory")
            }
            INCLUDEPATH *= $${Calendar_DIR}/include $${Calendar_DIR}/include/export
            LIBS *= -L$${Calendar_DIR}/lib -lLunarCalendar -lCalendar

  + cmake工程
    - 原码：
        + 子模块方式
  
              add_subdirectory(3th_libs/Calendar/Src)

        + 非子模块方式

                # Need include ${RabbitCommon_ROOT}/cmake/Translations.cmake
                if( "${RabbitCommon_ROOT}" STREQUAL "" )
                    set(RabbitCommon_ROOT $ENV{RabbitCommon_ROOT})
                    if( "${RabbitCommon_ROOT}" STREQUAL "" )
                        set(RabbitCommon_ROOT ${CMAKE_SOURCE_DIR}/../RabbitCommon)
                    endif()
                endif()

                if(DEFINED RabbitCommon_ROOT AND EXISTS ${RabbitCommon_ROOT}/Src)
                    add_subdirectory(${RabbitCommon_ROOT}/Src ${CMAKE_BINARY_DIR}/RabbitCommon)
                    include(${RabbitCommon_ROOT}/cmake/Translations.cmake)
                 else()
                     message("1. Please download RabbitCommon source code from https://github.com/KangLin/RabbitCommon")
                     message("   ag:")
                     message("       git clone https://github.com/KangLin/RabbitCommon.git")
                     message("2. Then set cmake value or environment variable RabbitCommon_ROOT to download root directory.")
                     message("   ag:")
                     message(FATAL_ERROR "       cmake -DRabbitCommon_ROOT= ")
                endif()

                set(Calendar_DIR $ENV{Calendar_DIR} CACHE PATH "Set Calendar source code root directory.")
                if(EXISTS ${Calendar_DIR}/Src)
                    add_subdirectory(${Calendar_DIR}/Src ${CMAKE_BINARY_DIR}/Calendar)
                else()
                    message("1. Please download Calendar source code from https://github.com/KangLin/Calendar")
                    message("   ag:")
                    message("       git clone https://github.com/KangLin/Calendar.git")
                    message("2. Then set cmake value or environment variable Calendar_DIR to download root directory.")
                    message("    ag:")
                    message(FATAL_ERROR "       cmake -DCalendar_DIR= ")
                endif()

    - 库方式:

        + Cmake 参数指定 Calendar_DIR 到库安装目录

            FIND_PACKAGE(Calendar)

        + 在 CMakeLists.txt 中增加头文件和库文件
        
                SET(APP_LIBS ${PROJECT_NAME} ${QT_LIBRARIES})
                if(Calendar_FOUND)
                    target_compile_definitions(${PROJECT_NAME}
                                PRIVATE -DCalendar)
                    target_include_directories(${PROJECT_NAME}
                                PRIVATE "${Calendar_INCLUDE_DIRS}/Src"
                                        "${Calendar_INCLUDE_DIRS}/Src/export")
                    set(APP_LIBS ${APP_LIBS} ${Calendar_LIBRARIES})
                endif()
                target_link_libraries(${PROJECT_NAME} ${APP_LIBS})
        
- 加载翻译资源
  + 用库中提供的函数

        CTasksTools::Instance()->InitResource();

  + 自定义

        QString szPre;    
        #if defined(Q_OS_ANDROID) || _DEBUG
            szPre = ":/Translations";
        #else
            szPre = qApp->applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "translations";
        #endif
        m_Translator.load(szPre + "/Calendar_" + QLocale::system().name() + ".qm");
        qApp->installTranslator(&m_Translator);

### 贡献

- [问题](https://github.com/KangLin/Calendar/issues)
- [贡献者](https://github.com/KangLin/Calendar/graphs/contributors)

### [许可协议](License.md "License.md")
