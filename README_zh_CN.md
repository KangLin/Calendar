## 任务

================================================

作者：康林（kl222@126.com)

[<img src="Resource/Image/English.png" alt="英语" title="英语" width="16" height="16" />英语](README.md)

[![Appveyor 编译状态](https://ci.appveyor.com/api/projects/status/hw8wsnwinrnohhda/branch/master?svg=true)](https://ci.appveyor.com/project/KangLin/tasks/branch/master)
[![Travis 编译状态](https://travis-ci.org/KangLin/Tasks.svg?branch=master)](https://travis-ci.org/KangLin/Tasks)
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

- [x] 眼睛护士: 保护视力
- [x] 自定义任务
- [x] 日历
    - [x] 生日提醒（年周期提醒）,包括农历
    - [x] 月周期提醒
    - [x] 周周期提醒
    - [x] 自定义周期
- [x] 便签
- 跨平台，支持多操作系统
  + [x] Windows
  + [x] Linux、Unix
  + [x] Android
  + [ ] Mac os
  + [ ] IOS

Mac os 和 IOS ，本人没有相应设备，请有相应设备的同学自己编译，测试。

### 屏幕截图

![Calendar](Resource/Image/ScreenShot/Calendar_zh_CN.PNG)
![Sticky](Resource/Image/ScreenShot/Sticky_zh_CN.png)
![Tasks](Resource/Image/ScreenShot/Tasks_zh_CN.PNG)

### 捐赠
本软件如果对你有用，或者你喜欢它，请你捐赠，支持作者。谢谢！

- 捐赠(大于￥20)：  
![捐赠( 大于 ￥20 )](https://github.com/KangLin/RabbitCommon/raw/master/Src/Resource/image/Contribute.png "捐赠(大于￥20)")

- 捐赠￥20  
![捐赠￥20](https://github.com/KangLin/RabbitCommon/raw/master/Src/Resource/image/Contribute20.png "捐赠￥20")

### [下载安装包](https://github.com/KangLin/Tasks/releases/latest)

- linux
    - [Tasks_v0.1.8.tar.gz](https://github.com/KangLin/Tasks/releases/download/v0.1.8/Tasks_v0.1.8.tar.gz)  
      AppImage格式的执行程序，可直接运行在linux系统，详见：https://appimage.org/  
      使用:    
      1. 解压。复制Tasks_v0.1.8.tar.gz到安装目录，然后解压：

                mkdir Tasks
                cd Tasks
                cp $DOWNLOAD/Tasks_v0.1.8.tar.gz .
                tar xvfz Tasks_v0.1.8.tar.gz

      2. 安装
        
                ./install.sh install
        
      3. 如果需要，卸载
        
                ./install.sh remove

- ubuntu
    - [tasks_0.1.8_amd64.deb](https://github.com/KangLin/Tasks/releases/download/v0.1.8/tasks_0.1.8_amd64.deb)  
  deb 安装包,可用于　Ubuntu
  
- windows
    - [Tasks-Setup-v0.1.8.exe](https://github.com/KangLin/Tasks/releases/download/v0.1.8/Tasks-Setup-v0.1.8.exe)  
  Windows安装包，支持 Windows xp 以上系统 

- android
    + [android-build-debug.apk](https://github.com/KangLin/Tasks/releases/download/v0.1.8/android-build-debug.apk)

### 依赖
- [RabbitCommon](https://github.com/KangLin/RabbitCommon)
  
        git clone https://github.com/KangLin/RabbitCommon.git

- [LunarCalendar](https://github.com/KangLin/LunarCalendar)

### 编译
- 建立并进入build目录

        git clone --recursive https://github.com/KangLin/Tasks.git
        cd Tasks
        mkdir build

- 编译
        cd build
        qmake ../Tasks.pro RabbitCommon_DIR=
        make install

- 用 cmake

      cd build
      cmake .. -DQt5_DIR=${QT_ROOT}/lib/cmake/Qt5 -DRabbitCommon_DIR=
      cmake --build .
      
- 安装注意  
Qt因为版权原因，没有提供openssl动态库，所以必须自己复制openssl的动态库到安装目录下。
    + windows
        - 如果是32的，可以在Qt安装程序Tools\QtCreator\bin目录下，找到openssl的动态库（libeay32.dll、ssleay32.dll）
        - 如果是64位，则需要自己下载openssl的二进制安装包。
    + linux

        ```
        sudo apt-get install libssl1.1
        ```

### 使用
- 直接用源码
  + 是QT工程
    - 库方式:
    在项目文件中加入下列语句：

            isEmpty(Tasks_DIR): Tasks_DIR=$ENV{Tasks_DIR}
            isEmpty(Tasks_DIR){
                message("1. Please download Tasks source code from https://github.com/KangLin/Tasks")
                message("   ag:")
                message("       git clone https://github.com/KangLin/Tasks.git")
                message("2. Build the project, get library")
                error("2. Then set value Tasks_DIR to library root dirctory")
            }
            INCLUDEPATH *= $${Tasks_DIR}/include $${Tasks_DIR}/include/export
            LIBS *= -L$${Tasks_DIR}/lib -lLunarCalendar -lTasks

  + cmake工程
    - 原码：
        + 子模块方式
  
              add_subdirectory(3th_libs/Tasks/Src)
      
        + 非子模块方式
    
                set(Tasks_DIR $ENV{Tasks_DIR} CACHE PATH "Set Tasks source code root directory.")
                if(EXISTS ${Tasks_DIR}/Src)
                    add_subdirectory(${Tasks_DIR}/Src ${CMAKE_BINARY_DIR}/Tasks)
                else()
                    message("1. Please download Tasks source code from https://github.com/KangLin/Tasks")
                    message("   ag:")
                    message("       git clone https://github.com/KangLin/Tasks.git")
                    message("2. Then set cmake value or environment variable Tasks_DIR to download root dirctory.")
                    message("    ag:")
                    message(FATAL_ERROR "       cmake -DTasks_DIR= ")
                endif()
                
    - 库方式:
    
        + Cmake 参数指定 Tasks_DIR 到库安装目录
        
            FIND_PACKAGE(Tasks)
        
        + 在 CMakeLists.txt 中增加头文件和库文件
        
                SET(APP_LIBS ${PROJECT_NAME} ${QT_LIBRARIES})
                if(Tasks_FOUND)
                    target_compile_definitions(${PROJECT_NAME}
                                PRIVATE -DTasks)
                    target_include_directories(${PROJECT_NAME}
                                PRIVATE "${Tasks_INCLUDE_DIRS}/Src"
                                        "${Tasks_INCLUDE_DIRS}/Src/export")
                    set(APP_LIBS ${APP_LIBS} ${Tasks_LIBRARIES})
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
        m_Translator.load(szPre + "/Tasks_" + QLocale::system().name() + ".qm");
        qApp->installTranslator(&m_Translator);

### 贡献

问题：https://github.com/KangLin/Tasks/issues  
项目位置：https://github.com/KangLin/Tasks

### [许可协议](License.md "License.md")
