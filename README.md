## Tasks

=========================================================

Author: KangLin (kl222@126.com)

[<img src="Resource/Image/china.png" alt="Chinese" title="Chinese" width="16" height="16"/>Chinese](README_zh_CN.md)
------------------------------------------------

### Features

- [x] Eye Nurse： Vision protection
- [x] Custom task
- [x] calendar
     - [x] Birthady(Year cycle)
     - [x] Month cycle
     - [x] Week cycle
     - [x] Custom cycle
- [x] Sticky

------------------------------------------------

[![Appveyor build status](https://ci.appveyor.com/api/projects/status/hw8wsnwinrnohhda?svg=true)](https://ci.appveyor.com/project/KangLin/tasks)
[![Travis build Status](https://travis-ci.org/KangLin/Tasks.svg?branch=master)](https://travis-ci.org/KangLin/Tasks)

------------------------------------------------
### Depend
- [RabbitCommon](https://github.com/KangLin/RabbitCommon)
  
        git clone https://github.com/KangLin/RabbitCommon.git

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
Qt does not provide openssl dynamic library for copyright reasons, so you must copy the dynamic library of openssl to the installation directory.
     - If it is 32, you can find the dynamic library of openssl (libeay32.dll, ssleay32.dll) in the Qt installer Tools\QtCreator\bin directory.
     - If it is 64-bit, you will need to download the binary installation package for openssl yourself.
------------------------------------------------
### Use
- Direct source code

  + Is a QT project, directly introduces Tasks.pri

         Include(Tasks.pri)

------------------------------------------------

### Download
https://github.com/KangLin/Tasks/releases/latest

- Tasks_0.0.7-2-gfba5878.tar.gz  
  The AppImage format executable can be run directly on the Linux system, see: https://appimage.org/  

  Usage:
    1. Decompress

      ```
      mkdir Tasks
      cd Tasks
      tar xvfz Tasks_0.0.7-2-gfba5878.tar.gz
      ```

  2. install

      ```
      install.sh install
      ```

  3. If you want to uninstall

      ```
      install.sh remove
      ```

- tasks_0.0.7-2-gfba5878_amd64.deb  
   Deb installation package for Ubuntu
  
- Tasks-Setup-0.0.7-2-gfba5878.exe  
   Windows installation package, support for Windows xp and above
   
------------------------------------------------

## Donation
- Donation (greater than ¥20):  
![donation (greater than ¥20)](Src/Resource/image/Contribute.png "donation (greater than ¥20)")

- Donate ¥20  
![donation ¥20](Src/Resource/image/Contribute20.png "donation ¥20")

------------------------------------------------

### [License Agreement](License.md "License.md")
