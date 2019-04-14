## 任务

================================================

作者：康林（kl222@126.com)

[<img src="Resource/Image/English.png" alt="英语" title="英语" width="16" height="16" />英语](README.md)

------------------------------------------------

### 功能

- [x] 眼睛护士: 保护视力
- [x] 自定义任务
- [ ] 日历
    - [ ] 生日提醒（年周期提醒）,包括农历
    - [ ] 月周期提醒
    - [ ] 周周期提醒
    - [ ] 自定义周期
- [x]  便签

------------------------------------------------

[![编译状态](https://ci.appveyor.com/api/projects/status/hw8wsnwinrnohhda/branch/master?svg=true)](https://ci.appveyor.com/project/KangLin/tasks/branch/master)

------------------------------------------------

### 编译
- 建立并进入build目录

        git clone --recursive https://github.com/KangLin/Tasks.git
        cd Tasks
        mkdir build

- 编译

        qmake Tasks.pro
        make install

- 安装注意  
Qt因为版权原因，没有提供openssl动态库，所以必须自己复制openssl的动态库到安装目录下。
    - 如果是32的，可以在Qt安装程序Tools\QtCreator\bin目录下，找到openssl的动态库（libeay32.dll、ssleay32.dll）
    - 如果是64位，则需要自己下载openssl的二进制安装包。
    
------------------------------------------------

### 使用
- 直接用源码
  + 是QT工程
    - 子模块方式：
      + 增加子模块：
      
            git submodule add https://github.com/KangLin/Tasks.git 3th_libs/Tasks
      
      + 在工程文件(.pro)中直接引入 Tasks.pri

            include(3th_libs/Tasks/Tasks.pri)

    - 非子模块方式：
      + 下载源码：https://github.com/KangLin/Tasks
      + 在环境变量（Tasks_DIR） 或 QMAKE参数 （Tasks_DIR） 
        中指定 Tasks 源码根目录的位置，然后在主工程文件（.pro）中加入下列：
    
            isEmpty(Tasks_DIR): Tasks_DIR=$$(Tasks_DIR)
            !isEmpty(Tasks_DIR): exists("$${Tasks_DIR}/Src/Tasks.pri"){
                DEFINES += Tasks
                include($${Tasks_DIR}/Src/Tasks.pri)
            } else{
                message("1. Please download Tasks source code from https://github.com/KangLin/Tasks ag:")
                message("   git clone https://github.com/KangLin/Tasks.git")
                message("2. Then set value Tasks_DIR to download root dirctory")
            }
    
  + cmake工程
  - 子模块方式
  
          add_subdirectory(3th_libs/Tasks/Src)
      
  - 非子模块方式
  
          set(Tasks_DIR $ENV{Tasks_DIR} CACHE PATH "Set Tasks source code root directory.")
          if(EXISTS ${Tasks_DIR}/Src)
              add_subdirectory(${Tasks_DIR}/Src ${CMAKE_BINARY_DIR}/Tasks)
          else()
              message(FATAL_ERROR 
              "1. Please download Tasks source code from https://github.com/KangLin/Tasks ag:"
              "   git clone https://github.com/KangLin/Tasks.git"
              "2. Then set cmake value or environment variable Tasks_DIR to download root dirctory."
              "    ag:"
              "       cmake -DTasks_DIR= ")
          endif()

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

------------------------------------------------

### 下载
https://github.com/KangLin/Tasks/releases/latest

------------------------------------------------

## 捐赠
- 捐赠(大于￥20)：  
![捐赠( 大于 ￥20 )](Src/Resource/image/Contribute.png "捐赠(大于￥20)")

- 捐赠￥20  
![捐赠￥20](Src/Resource/image/Contribute20.png "捐赠￥20")

------------------------------------------------

### [许可协议](License.md "License.md")
