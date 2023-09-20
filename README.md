# coursework-a-table-pet-Haro

使用C++与Qt写的一个桌面宠物，命名为Haro（neta高达），[B站传送门](https://www.bilibili.com/video/BV1Zv4y117Xt)

Haro (Gun-neta), A desktop pet written with C++ and Qt. [Video](https://www.bilibili.com/video/BV1Zv4y117Xt)

## Build

## Prerequisites

Haro uses `QMediaPlaylist` which has been removed in `Qt 6.X` to display music list, so you need to intall `Qt 5.X` to build Haro.

### Build with qmake

Clone this repo, open your `Qt Creator` and `Open Project...` with `Haro.pro`, then you can build Haro in `Qt Creator`.

### Build with CMake

You can open this project with `VS Code`or `Qt Creator`.

Clone this repo, open your `Qt Creator` and `Open Project...` with `CMakeLists.txt`, then you can build Haro in `Qt Creator`.

Clone this repo, open the folder with your `VS Code`, right click `CMakeLists.txt` and select `Clean Reconfigure All Projects` and `Clean Rebuild All Projects`, done!
