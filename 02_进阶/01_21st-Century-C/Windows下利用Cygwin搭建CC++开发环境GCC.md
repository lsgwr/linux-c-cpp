# Windows下利用Cygwin搭建C/C++开发环境GCC

> 来源：https://www.cnblogs.com/xym4869/p/12232331.html

## 1.下载cygwin
下载地址：http://www.cygwin.com/
## 2.下载完成后点击运行
+ install from internet
+ All users
+ Direct Connection
+ 镜像选择https://mirrors.huaweicloud.com
+ 选择要安装的组件，搜索 gcc-core、gcc-g++、make、gdb、binutils，以上所有项目都在 devel 文件夹下

## 3.后面要新增组件

> 只需要重新运行setup-x86_64.exe，在Select Packages界面新增勾选自己想安装的组件即可