## [<img src="App/AppIcon.ico" title="日历" width="16" height="16"/>日历](https://github.com/KangLin/Calendar)


作者：康林（kl222@126.com)

- 项目位置: https://github.com/KangLin/Calendar
- [项目主页](https://kanglin.github.io/Calendar/)

[<img src="Resource/Image/English.png" alt="英语" title="英语" width="16" height="16" />英语](README.md)

[![Appveyor 编译状态](https://ci.appveyor.com/api/projects/status/hw8wsnwinrnohhda/branch/master?svg=true)](https://ci.appveyor.com/project/KangLin/Calendar/branch/master)
[![Travis 编译状态](https://travis-ci.org/KangLin/Calendar.svg?branch=master)](https://travis-ci.org/KangLin/Calendar)
[![GitHub stars](https://img.shields.io/github/stars/KangLin/Calendar)](https://github.com/KangLin/Calendar/stars)
[![GitHub forks](https://img.shields.io/github/forks/KangLin/Calendar)](https://github.com/KangLin/Calendar/forks)
[![GitHub issues](https://img.shields.io/github/issues/KangLin/Calendar)](https://github.com/KangLin/Calendar/issues)
[![Current release](https://img.shields.io/github/release/KangLin/Calendar)](https://github.com/KangLin/Calendar/releases)
[![All releases downloads](https://img.shields.io/github/downloads/KangLin/Calendar/total)](https://github.com/KangLin/Calendar/releases)

------------------------------------------------

* [功能](#功能)
* [屏幕截图](#屏幕截图)
* [捐赠](#捐赠)
* [下载安装包](#下载安装包)
* [依赖](#依赖)
* [编译](#编译)
* [使用](#使用)
* [贡献](#贡献)
* [许可协议](#许可协议)

### 功能

- [x] 日历
    - [x] 生日提醒（年周期提醒）,包括农历
    - [x] 月周期提醒
    - [x] 周周期提醒
    - [x] 自定义周期
- [x] 自定义任务
  - [x] 眼睛护士: 保护视力
- [x] 便签
- 跨平台，支持多操作系统(https://doc.qt.io/qt-5/supported-platforms.html)
  + [x] Windows
  + [x] Linux、Unix
  + [x] Android
  + [ ] Mac os
  + [ ] IOS
  
Mac os 和 IOS ，本人没有相应设备，请有相应设备的同学自己编译，测试。

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
 
[![捐赠](https://gitee.com/kl222/RabbitCommon/raw/master/Src/Resource/image/Contribute.png "捐赠")](https://gitee.com/kl222/RabbitCommon/raw/master/Src/Resource/image/Contribute.png "捐赠") 

### [下载安装包](https://github.com/KangLin/Calendar/releases/latest)

- windows
    - [Calendar-Setup-v1.0.3.exe](https://github.com/KangLin/Calendar/releases/download/v1.0.3/Calendar-Setup-v1.0.3.exe)
  Windows安装包，支持 Windows xp 以上系统

- android
    + [Calendar_v1.0.3.apk](https://github.com/KangLin/Calendar/releases/download/v1.0.3/Calendar_v1.0.3.apk)

- linux
    - [Calendar_v1.0.3.tar.gz](https://github.com/KangLin/Calendar/releases/download/v1.0.3/Calendar_v1.0.3.tar.gz)  
      AppImage格式的执行程序，可直接运行在linux系统，详见：https://appimage.org/  
      使用:    
      1. 解压。复制 Calendar_v1.0.3.tar.gz 到安装目录，然后解压：

            ```
            mkdir Calendar
            cd Calendar
            cp $DOWNLOAD/Calendar_v1.0.3.tar.gz .
            tar xvfz Calendar_v1.0.3.tar.gz
            ```
            
      2. 安装
        
            ```
            ./install1.sh install_autostart Calendar
            ```
        
      3. 如果需要，卸载
        
            ```
            ./install1.sh remove Calendar
            ```

- ubuntu
    - [Calendar_1.0.3_amd64.deb](https://github.com/KangLin/Calendar/releases/download/v1.0.3/Calendar_1.0.3_amd64.deb)  
  deb 安装包,可用于　Ubuntu

### 依赖
- [Qt (LGPL v2.1)](http://qt.io/)
- [RabbitCommon](https://github.com/KangLin/RabbitCommon)
  
        git clone https://github.com/KangLin/RabbitCommon.git
        
- [LunarCalendar](https://github.com/KangLin/LunarCalendar)

### 编译
- 建立并进入build目录

        git clone --recursive https://github.com/KangLin/Calendar.git
        mkdir build

- 编译

        cd build
        qmake ../Calendar.pro RabbitCommon_DIR=
        make install

  + 参数：
    - RabbitCommon_DIR: 指向 RabbitCommon 源码目录

- 用 cmake
  + CMAKE 参数：
    - [必选] Qt5_DIR: qt5 安装位置(指向Qt5Config.cmake的目录，默认为 安装目录/lib/cmake/Qt5)。  
                     详见：https://doc.qt.io/qt-5/cmake-get-started.html  
             或者 Qt6_DIR: qt6 安装位置(指向Qt6Config.cmake的目录，默认为 安装目录/lib/cmake/Qt6)
    - [必选] RabbitCommon_DIR: 指向 RabbitCommon 源码目录
    - [可选] CMAKE_INSTALL_PREFIX: 安装前缀
  + windows 或 linux
  
        cd build
        cmake .. -DCMAKE_INSTALL_PREFIX=`pwd`/install \
               -DCMAKE_BUILD_TYPE=Release \
               -DQt5_DIR=${QT_ROOT}/lib/cmake/Qt5 \
               -DRabbitCommon_DIR=
        cmake --build . --config Release --target install
        
  + android
    - 主机是linux
      + 编译

            cd build
            cmake .. -DCMAKE_BUILD_TYPE=Release \
               -DCMAKE_INSTALL_PREFIX=`pwd`/android-build \
               -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake \
               -DANDROID_ABI="armeabi-v7a with NEON" \
               -DANDROID_PLATFORM=android-18 \
               -DQt5_DIR= \
               -DRabbitCommon_DIR= 
            cmake --build . --config Release

    　+ 安装
        - 安装库和程序

              cmake --build . --config Release --target install/strip
              
        - 生成 APK

              cmake --build . --config Release --target APK
          
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
                -DQt5_DIR= ^
                -DRabbitCommon_DIR= 
             
      + 安装
        - 安装库和程序

            cmake --build . --config Release --target install/strip

        - 生成 APK

            cmake --build . --config Release --target APK

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
                error("2. Then set value Calendar_DIR to library root dirctory")
            }
            INCLUDEPATH *= $${Calendar_DIR}/include $${Calendar_DIR}/include/export
            LIBS *= -L$${Calendar_DIR}/lib -lLunarCalendar -lCalendar

  + cmake工程
    - 原码：
        + 子模块方式
  
              add_subdirectory(3th_libs/Calendar/Src)
      
        + 非子模块方式
    
                # Need include ${RabbitCommon_DIR}/cmake/Translations.cmake
                if( "${RabbitCommon_DIR}" STREQUAL "" )
                    set(RabbitCommon_DIR $ENV{RabbitCommon_DIR})
                    if( "${RabbitCommon_DIR}" STREQUAL "" )
                        set(RabbitCommon_DIR ${CMAKE_SOURCE_DIR}/../RabbitCommon)
                    endif()
                endif()

                if(DEFINED RabbitCommon_DIR AND EXISTS ${RabbitCommon_DIR}/Src)
                    add_subdirectory(${RabbitCommon_DIR}/Src ${CMAKE_BINARY_DIR}/RabbitCommon)
                    include(${RabbitCommon_DIR}/cmake/Translations.cmake)
                 else()
                     message("1. Please download RabbitCommon source code from https://github.com/KangLin/RabbitCommon")
                     message("   ag:")
                     message("       git clone https://github.com/KangLin/RabbitCommon.git")
                     message("2. Then set cmake value or environment variable RabbitCommon_DIR to download root dirctory.")
                     message("   ag:")
                     message(FATAL_ERROR "       cmake -DRabbitCommon_DIR= ")
                endif()

                set(Calendar_DIR $ENV{Calendar_DIR} CACHE PATH "Set Calendar source code root directory.")
                if(EXISTS ${Calendar_DIR}/Src)
                    add_subdirectory(${Calendar_DIR}/Src ${CMAKE_BINARY_DIR}/Calendar)
                else()
                    message("1. Please download Calendar source code from https://github.com/KangLin/Calendar")
                    message("   ag:")
                    message("       git clone https://github.com/KangLin/Calendar.git")
                    message("2. Then set cmake value or environment variable Calendar_DIR to download root dirctory.")
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
