# coursework-a-table-pet-Haro

Haro (Gun-neta), A desktop pet written with C++ and Qt. [Video](https://www.bilibili.com/video/BV1Zv4y117Xt)

[简体中文](README_CN.md)

## Build

### Prerequisites

Haro uses `QMediaPlaylist` which has been removed in `Qt 6.X` to display music list, so you need to intall `Qt 5.X` to build Haro.

### Build with qmake

Clone this repo, open your `Qt Creator` and `Open Project...` with `Haro.pro`, then you can build Haro in `Qt Creator`.

### Build with CMake

You can open this project with `VS Code`or `Qt Creator`.

Clone this repo, open your `Qt Creator` and `Open Project...` with `CMakeLists.txt`, then you can build Haro in `Qt Creator`.

Clone this repo, open the folder with your `VS Code`, right click `CMakeLists.txt` and select `Clean Reconfigure All Projects` and `Clean Rebuild All Projects`, done!

## Installation

### Windows

Download the latest installer from [release](https://github.com/Syize/coursework-a-table-pet-Haro/releases), and run.

**NOTE: On Windows, Qt's QSettings class uses the Windows registry to store some settings. Currently, Haro does not have code to completely remove these settings during uninstallation. So, if you wish to uninstall Haro, you may need to manually clear these settings. However, rest assured that Haro does not store any user tracking information in the registry; it only contains some configuration settings. For example:**

> Content of settings file on Linux

```ini
[General]
AutoStart=false
Body=6
Ear=4
WindowSize=400

[Coordinates]
X=1004
Y=176

[Game]
File="Executable File Path"
Hide=true
```

### Linux

Still learning how to package....
