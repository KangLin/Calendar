## Tasks

=========================================================

Author: KangLin (kl222@126.com)

[<img src="Resource/Image/china.png" alt="Chinese" title="Chinese" width="16" height="16"/>Chinese](README_zh_CN.md)
------------------------------------------------

### Features

- [x] Eye Nurse： Vision protection
- [x] Custom task
- [x] calendar
     - [x] Birthady(Year cycle), include lunar and solar
     - [x] Month cycle
     - [x] Week cycle
     - [x] Custom cycle
- [x] Sticky

------------------------------------------------

[![Appveyor build status](https://ci.appveyor.com/api/projects/status/hw8wsnwinrnohhda?svg=true)](https://ci.appveyor.com/project/KangLin/tasks)
[![Travis build Status](https://travis-ci.org/KangLin/Tasks.svg?branch=master)](https://travis-ci.org/KangLin/Tasks)

------------------------------------------------

## Donation
- Donation (greater than ¥20):  
![donation (greater than ¥20)](Src/Resource/image/Contribute.png "donation (greater than ¥20)")

- Donate ¥20  
![donation ¥20](Src/Resource/image/Contribute20.png "donation ¥20")

------------------------------------------------

### [Download setup package](https://github.com/KangLin/Tasks/releases/latest)

- linux
    - [Tasks_0.0.8.tar.gz](https://github.com/KangLin/Tasks/releases/download/0.0.8/Tasks_0.0.8.tar.gz)  
      The AppImage format executable can be run directly on the Linux system, see: https://appimage.org/  
      Usage:    
      1. Decompress. Copy Tasks_0.0.8.tar.gz to install directory, then decompress it:

                mkdir Tasks
                cd Tasks
                cp $DOWNLOAD/Tasks_0.0.8.tar.gz .
                tar xvfz Tasks_0.0.8.tar.gz

      2. install

                ./install.sh install

      3. If you want to uninstall

                ./install.sh remove

- ubuntu
    - [tasks_0.0.8_amd64.deb](https://github.com/KangLin/Tasks/releases/download/0.0.8/tasks_0.0.8_amd64.deb)  
   Deb installation package for Ubuntu

- windows
    - [Tasks-Setup-0.0.8.exe](https://github.com/KangLin/Tasks/releases/download/0.0.8/Tasks-Setup-0.0.8.exe)  
   Windows installation package, support for Windows xp and above

- android
    + [android-build-debug.apk](https://github.com/KangLin/Tasks/releases/download/0.0.8/android-build-debug.apk)
    
------------------------------------------------

### Depend
- [RabbitCommon](https://github.com/KangLin/RabbitCommon)
  
        git clone https://github.com/KangLin/RabbitCommon.git

- [LunarCalendar](https://github.com/KangLin/LunarCalendar)

### Compile
- Create and enter the build directory

        git clone --recursive https://github.com/KangLin/Tasks.git
        cd Tasks
        mkdir build

- Compile

        cd build
        qmake ../Tasks.pro RabbitCommon_DIR=
        make install

+ Use cmake

        cd build
        cmake .. -DQt5_DIR=${QT_ROOT}/lib/cmake/Qt5 -DRabbitCommon_DIR=
        cmake --build .
      
- Note  
    + windows
       If you build app. Qt does not provide openssl dynamic library for copyright reasons, so you must copy the dynamic library of openssl to the installation directory.
        - If it is 32, you can find the dynamic library of openssl (libeay32.dll, ssleay32.dll) in the Qt installer Tools\QtCreator\bin directory.
        - If it is 64-bit, you will need to download the binary installation package for openssl yourself.
  
    + linux
 
     ```
     sudo apt-get install libssl1.1
     ```

------------------------------------------------
### Use
- pro
    - Library mode:
     Add the following code to the project file:
   
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

- cmake
    + Source code
        + Submodule mode
  
              add_subdirectory(3th_libs/Tasks/Src)
      
        + Non-submodule mode
  
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

    + Library mode:

        + Cmake parameter Tasks_DIR specifies the installation root directory
        
            FIND_PACKAGE(Tasks)
        
        + Add libraries and include in CMakeLists.txt
        
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
                
------------------------------------------------

### Contribution

Question: https://github.com/KangLin/Tasks/issues  
Project location: https://github.com/KangLin/Tasks

------------------------------------------------
### [License Agreement](License.md "License.md")
