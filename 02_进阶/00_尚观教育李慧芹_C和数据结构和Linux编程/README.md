# 尚观教育李慧芹老师的系列课
> 讲解《Unix环境高级编程(第2版)》的第3~16章

## 一、课程视频
> 完整版在百度网盘里：`1.教程/03.C和C++/01_尚观教育`里，平时直接在B站上看也行，汇总下几个比较全的，主要是评论区可以找到一些比较有价值的代码和笔记

+ [Linux系统编程（李慧芹）](https://www.bilibili.com/video/BV1yJ411S7r6)
+ [李慧芹-C语言-数据结构-Linux系统编程-网络编程-全套教程](https://www.bilibili.com/video/BV1yJ411S7r6)
+ [史上最强最细腻的linux嵌入式C语言学习教程【李慧芹老师】](https://www.bilibili.com/video/BV18p4y167Md)

## 二、课程代码和笔记
+ [基于IPv4的流媒体广播系统](https://github.com/missFuture/IPv4_streaming_media)
+ [Linux系统编程：APUE部分的笔记](https://www.cnblogs.com/0xcafebabe/tag/APUE/)
+ [完整课程的笔记](https://github.com/impact-eintr/LinuxC)
+ [LinuxC学习笔记](https://blog.csdn.net/m0_46152793)

## 三、参考资料
+ [跟我一起写Makefile](https://seisman.github.io/how-to-write-makefile/index.html)
+ [APUE第三版完整材料](https://github.com/Lincheng1993/apue)

## 四、书的结构和学习顺序
> APUE主要学习了四部分内容：IO、文件系统、并发、进程间通信。

### ① IO：
> 第3、4、5、14章，第14章等进程间通信讲完再讲

+ 标准IO：`第5章`，优点是可移植性高，缺点是性能比系统 IO 差，且功能没有系统 IO 丰富。
+ 系统IO：`第3章`，因为是内核直接提供的系统调用函数，所以性能比标准 IO 高，但是可移植性比标准 IO 差。

### ② 文件系统
> 第4、6、7章

### ③ 并发
> 第10、11章

+ 信号 + 多进程：第10章
+ 多线程：第10章和第11章都有

### ④ 进程间通信(IPC：Inter Process Communication)：
> 第8、13、15、16章，第8章是进程基础(涉及多进程)，第13章是守护进程，15和16章都是进程间通信的内容

+ FIFO：管道；
+ System V：又称为 XSI，支持以下三种方式：
  + msg：消息队列；
  + sem：信号量；
  + shm：共享存储；
+ Socket：套接字（网络通信）；