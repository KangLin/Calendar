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
- 直接用源码。是QT工程，则直接引入Tasks.pri

        include(Tasks.pri)

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
