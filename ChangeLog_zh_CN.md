- v1.0.21
  - 增加日历类型选项

- v1.0.20
  - 使用 VCPKG_MANIFEST_DIR 重载 openssl 1.1
  - 使用 [RabbitCommon v2.2.1](https://github.com/KangLin/RabbitCommon/releases/tag/v2.2.1)

- v1.0.19
  - 修改 Change log 等文档位置，详见：RabbitCommon v2.1.0

- v1.0.18
  - 修改 debian 打包
  - 使用 RabbitCommon v2.0.0 的新的更新功能

- v1.0.17
  - 使用 LunarCalendar v1.0.0

- v1.0.16
  - 增加 android 动态权限
  - 使用 LunarCalendar v0.3.2

- v1.0.15
  - 自动化编译
    - 为 android 包增加签名

- v1.0.14
  - 在　org.Rabbit.Calendar.desktop　中增加 MimeType
  - 在 RabbitCommonUtils.cmake 中产生 pkg-config 配置文件
  - 更新 LunarCalendar 到 [v0.3.0](https://github.com/KangLin/LunarCalendar/blob/v0.3.0/ChangeLog.md)
  
- v1.0.13
  - 修复 DockDebugLog 崩溃. 详见: [RabbitCommon](https://github.com/KangLin/RabbitCommon/commit/af2e434e39af35876113436ead2a946efcf74199)
  - 修改菜单
  - 更新 2024 年中国节假日

- v1.0.12
  - 修复自启动错误。详见：[RabbitCommon](https://github.com/KangLin/RabbitCommon/commit/12d5686994ea8f5decb0cf211547ba548ab9f3e9)

- v1.0.11
  - 用 QFileDialog::getExistingDirectory 替换 RabbitCommon::CDir::GetOpenDirectory 等
  
- v1.0.10
  - 修改自动化编译
  
- v1.0.9
  - 增加：更新 xml 文件
  - 修复: windows 资源

- v1.0.8
  - 使用 RabbitCommon v2
  - 删除 qmake 管理工程
  - Android 自动编译

- v1.0.7
  - 测试更新

- v1.0.6
  - 重命名 tag.sh 到 deploy.sh
  - 修改日志（详见：RabbitCommon)
  - 修复动态库错误
  
- v1.0.5
  - CI: Modify update release

- v1.0.4
  - 增加镜像库
  - 修复除 0 引起的崩溃。影响前面所有发行版本。此错误是 RabbitCommon 引起的。
    详见：RabbitCommon: 7ed300a206d8a36c30003b6c19ad181682d0ff5f
  - 支持 Qt6
  - 增加 2022 年假期
  - 增加 2023 年假期
  - CI: 增加 github actions
  - 更新 RabbitCommon 更新软件
  - 使用图标主题

- v1.0.3
  - 测试 github action 更新发行
  - 用 RabbitCommon::CStyle 更改样式
  - 增加后台任务线程

- v1.0.2
  - 以春节做为一年的第一天
  - 增加支持 Qt6

- v1.0.1
  - 修改样式
  - 增加 2021 年节假日

- v1.0.0
  - FIX: android 运行失败
  - 修改应用图标
  - 重命名为日历

- v0.3.5
  - FIX: 修改关于对话框大小
  - 修改自动化编译，用 ubuntu 系统自带的 qt
  - 修改 install.nsi ，禁止VC库安装后重启
  - 修改 2020 年春节假期
  - Android: 增加 openssl 到 APK 中

- v0.3.4
  - 修改中国假日数据库目录为用户数据库目录

- v0.3.3
  - 修改 table 尺寸

- v0.3.2
  - 测试更新
  - 增加 Android 签名

- v0.3.1
  - 测试更新

- v0.3.0
  - 测试更新

- v0.2.9
  - 测试更新

- v0.2.8
  - 修改更新

- v0.2.7
  - 增加自动化编译

- v0.2.6
  - 增加便签版本号

- v0.2.5
  - 完善 cmake

- v0.2.4
  - 日历中增加中国假日

- v0.2.3
  - 根据本地语言，决定日历类型

- v0.2.2
  - 修改便签BUG

- v0.2.1
  - android 下增加触屏滑动
  - 增加今天图标
  - 修改主窗口
  - 修改日历键盘选择日期BUG

- v0.2.0
  - 修改 AndroidManifest.xml

- v0.1.9

- v0.1.8
  - Android: 移动 authors.md, changelog.md to assets in android
  - 固定资源 BUG
  - FIX BUG

- v0.1.7
  - 修改系统启动时自动
  - 固定 BUG

- v0.1.6
  - 使用 RabbitCommon v1.0.0
  - 固定 BUG

- v0.1.5
  - 修改 install.sh

- v0.1.4
  - 只做linux下appimage更新测试

- v0.1.3
  - 修改打包 tar.gz 内容
  - 增加管理员认证

- v0.1.2
  - 修改打包 tar.gz

- v0.1.1
  - 增加屏幕截图
  - 增加 update_linux_appimage.xml

- v0.1.0
  - 重新使用带 v 前缀版本号

- 0.0.10
  - 修改更新，并测试更新

- 0.0.9
  - 修改ANDROID下的问题

- 0.0.8
  - 更新RabbitCommon,使用新的更新功能
  - 增加农历年任务提醒（农历生日）
  - 增加 android CI 

- 0.0.7
  - 增加 appimagep 安装
  - ci 中增加 linux 下测试

- 0.0.6
  - 自定义日期周期

- 0.0.5
  - 增加日历任务提醒
    - 生日（年周期）
    - 月周期
    - 周周期

- 0.0.4
  - 增加屏幕唤醒
  - 用QScrollArea做为容器窗口，适应ANDROID系统
  - 增加日历
  - 增加ubuntu分发

- v0.0.3
  - 修改主界面
  - 任务列表与便签列表窗体自带工具栏
  - 提供库
  - 修改工程目录结构
  - 增加CMAKE管理工程

- v0.0.2
  - 任务编辑
  - 在线更新
  - 便签

- v0.0.1
  - 眼睛护士：保护视力
