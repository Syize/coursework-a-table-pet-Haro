# coursework-a-table-pet-Haro

使用C++与Qt写的一个桌面宠物，命名为Haro（neta高达），[B站传送门](https://www.bilibili.com/video/BV1Zv4y117Xt)

## 构建

### 注意

Haro使用`QMediaPlaylist`来显示音乐列表，但是在`Qt 6.X`版本中该类已经被移除，所以Haro只兼容`Qt 5.X`。

### 使用qmake构建

克隆本仓库，在`Qt Creator`中打开项目，选择`Haro.pro`文件。

### 使用CMake构建

你可以使用`VS Code`或者`Qt Creator`构建。

克隆本仓库，在`Qt Creator`中打开项目，选择`CMakeLists.txt`文件。

克隆本仓库，在`VS Code`中打开项目，选择`CMakeLists.txt`文件。

## 安装

### Windows

从最新的[release](https://github.com/Syize/coursework-a-table-pet-Haro/releases)中下载安装包并运行。 

**注意：在Windows上，"Qt的QSettings类会使用Windows的注册表来存储一些设置，目前Haro没有编写在卸载时完全清除这些设置的代码，因此如果你想要卸载Haro的话，有可能需要手动清除这些设置。但是不用担心，Haro不会在注册表里面存储跟踪用户的信息，仅仅是一些设置信息。例如**

> 以下是Linux平台记录的设置项，与Windows上的条目相同

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

还在学习打包中...
