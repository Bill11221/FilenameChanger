# FilenameChanger

FilenameChanger 是一个基于 Qt Widgets 和 C++17 的 Windows 桌面应用程序，用于批量重命名图片文件。该工具提供简单直观的图形用户界面，用户可以通过选择文件夹，然后一键执行重命名操作，将文件夹内图片按顺序重命名为“1.xxx”，“2.xxx”等格式，保留原文件扩展名。

## 特性

- **简单易用的 GUI**：选择文件夹后直接显示文件夹路径与操作日志，重命名过程清晰直观。
- **批量处理**：自动检测文件夹内指定格式的图片（支持 jpg、jpeg、png、bmp、gif）文件，并依照文件名排序依次重命名。
- **错误提示**：针对文件夹不存在、未选择文件夹等异常情况，给出友好的错误提示信息。
- **跨平台部署**：基于 Qt 开发，使用 windeployqt 工具可方便地打包所需的 DLL 文件，构建纯 GUI 应用程序，无黑色 CMD 窗口。

## 截图

![程序截图](screenshot.png)
*(请将截图文件命名为 screenshot.png 并放在仓库中)*

## 目录结构
FilenameChanger/ ├── README.md ├── filenamechanger.pro ├── main.cpp ├── mainwindow.cpp ├── mainwindow.h └── (其他构建文件)


## 编译与构建

### 环境要求

- Qt 6.x（也可使用 Qt 5，但建议使用较新版本）
- 支持 C++17 的编译器（如 MinGW 64-bit 或 MSVC）
- Windows 系统（GUI 应用程序，不显示 CMD 窗口）

### 编译步骤

1. **导入工程**  
   在 Qt Creator 中打开 `filenamechanger.pro` 工程文件。

2. **清理与重构**  
   - 执行“清理项目 (Clean Project)”
   - 运行 “Run qmake”
   - 选择“全部重建 (Rebuild Project)”

3. **编译运行**  
   编译通过后，生成的 exe 文件为 `filenamechanger.exe`。直接运行该 exe 文件将启动应用程序。

### 部署说明

在发布时（或独立运行时），需要将 Qt 依赖的 DLL 文件一并部署。建议使用 Qt 自带的 `windeployqt` 工具：

```cmd
windeployqt path\to\filenamechanger.exe

该命令会将所有运行所需的 DLL 文件和平台插件复制到 exe 文件所在目录。

使用方法
启动程序后，在主界面的文本框中点击“选择文件夹”按钮，选择包含图片文件的目标文件夹。

点击“开始重命名”按钮，程序会依照文件名排序后将图片文件依次重命名为“1.xxx”，“2.xxx”等格式，操作日志会显示在窗口下方。

操作结束后，在日志中查看重命名结果。

项目文件说明
filenamechanger.pro
工程文件，配置了使用 Qt Widgets 模块以及 C++17 标准，不包含 CONFIG += console 以确保运行时不显示 CMD 窗口。

main.cpp
主程序入口，负责创建 QApplication 和主窗口对象。

mainwindow.h / mainwindow.cpp
定义并实现主窗口功能，包括文件夹选择、重命名操作和日志显示功能。

问题反馈
如果你在使用或编译过程中遇到问题，欢迎在 GitHub Issues 中留言，我会尽快处理和回复。

许可证
本项目采用 MIT 许可证 开源发布。请参阅 LICENSE 文件了解更多详情。
