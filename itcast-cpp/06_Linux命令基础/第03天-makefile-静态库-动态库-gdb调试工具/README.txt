
--------------------------------------

		文件				目录
	
r	可以查文件内容			可以查看目录(文件的)内容	
	cat/more/head...vim			ls /get

w	文件的内容可修改、删除		可以在目录内创、修改、删除
	vim对文件写操作			rm、mkdir、touch、mv、cp... /put
	> / >>

x	可以运行(可执行程序、脚本)	目录可以被打开



MMU  单位：4K  一个page

.data: 初始化为非0的全局变量、初始化为非0静态局部变量

.bss: 初始化为0全局变量、初始化为0的静态变量、未初始化的全局、静态变量

.text: 代码段

.rodata: 只读数据段



-----------------------------------------


函数库：本质：一组函数。具有相近的功能或操作同一数据结构。strcpy/strcmp/strcat/strlen/strstr/strchr/strtok...  <string.h>

	bubble_sort / select_sort / quick_sort / insert_sort  <mysort.h> 


	作用：	1. 代码复用：软件开发的大部分时间用在应用程序设计上。而不是花在处理底层的细节上。(面向对象程序设计也体现了代码复用)

		   硬件——系统调用——标准库——用户库——应用程序 (层层复用)

		2. 程序积累

	
	发布形式：	1. 源码形式发布    缺点：1. 保密性差  2.  编译程序耗时、平台、编译器版本

					   优点：方便使用者学习和研究

			2. 二进制形式	   优缺点 与上相反

	标准C库libc.so.6

-----------------------------------------


静态库：

	机制：复制静态库作为程序代码段的一部分。

	优点：将函数库中的函数本地化。寻址方便，速度快。（库函数调用效率 == 自定义函数使用效率） 

	缺点：消耗系统资源较大。每个进程使用静态库都要复制一份。无端浪费内存

	使用场景：多应用于核心程序，保证时效性，可以忽视空间。 

	制作：
		1. gcc add.c sub.c mul.c -c 		——>得到*.o

		2. ar rs libmymath.a add.o sub.o mul.o 	——>得到静态库

			ar工具不包含在gcc中

			r更新、c创建、s建立索引
	
			file libmymath.a 		——>查看库信息
	
		3. gcc main.c -L ./ -l mymath -o app 	——>使用静态库


	使用：L:指定静态库所在目录位置；l：指定静态库名字 I：指定头文件所在目录位置

	
-----------------------------------------
	
	
动态库（共享库）：


	机制：共享代码(不共享数据)

	优点：节省内存(共享)、易于更新(动态链接)  ./a.out   《--- libc.so

	缺点：相较于静态库函数调用速度略慢(延迟绑定机制)

	使用场景：1. 对程序执行速度要求不是很强烈，而相对于系统资源有一定要求的场景

		  2. 对于更新比较频繁的程序

			1）停止运行程序
			2）使用新库覆盖旧库(保证新旧库名称一致，接口一致) “接口”
			3）重新启动程序。

	重点强调：1. 动态库是否加载到内存，取决于程序是否运行

		  2. 动态库加载到内存的位置不固定----动态链接器


	制作：

	1. gcc -fPIC add.c mul.c sub.c -c （-fPIC：生成“与位置无关”的目标文件*.o）
	
	2. gcc -shared -o libmymath.so add.o mul.o sub.o
	
	3. gcc main.c -L库路径 -l库名 -I头文件名  -o app
	
	4. ./app --> 出错 	
	
	   原因：动态连接器 ld-linux.so.2 搜寻动态库的路径未指定，

		 执行ldd app发现动态链接器找不到 libmymath 库。
	
	   指定方法：

		1. 环境变量法：export LD_LIBRARY_PATH=./ 将当前目录加入环境变量，但是终端退出了就无效了。

		2. 配置文件法：将上条写入家目录下.bashrc文件中	（永久生效，设置到~/.bashrc）

		3. 拷贝法：直接将libmymath.so文件拷贝到/usr/lib/目录下。(受libc库的启发)

		4. 缓存文件法：将libmymath.so所在绝对路径加入到/etc/ld.so.conf文件，

		   使用sudo ldconfig -v 动态更新/etc/ld.so.cache文件(2进制文件)
	
	*5. 指定动态库的soname
	
	    gcc -shared -Wl,-soname,libmymath.so.1 -o libmymath.so.1.10 add.o mul.o sub.o
	
	*6. 创建动态库的LinkerName
	
	    ln -s libmymath.so.1.10 libmymath.so



动、静态库共存时：

	编译器默认使用.so的动态库，找不到才使用静态库。

	-static可以直接指定使用静态库。
	
	objdump -dS app > out

	注意比较加了static和没有加static的可执行文件大小，及内部printf的地址。


-----------------------------------------
gdb：

	使用场景：程序编译无误，但是有逻辑错误。 


	加-g 编译 ---> gdb xxx  

	list 1 ---> b 行号
	
	info b  查看断点信息。
	
	disable/enable  断点号——设置断点非使能/使能。
	
	delete 断点号——删除断点
	
	b 行号 if i=5  设置条件断点，只有i=3时断点生效。
	
	run  ----  start
	
	p 变量名——查看变量值
	display——跟踪变量
	undisplay——取消跟踪
	ptype 变量名——查看变量类型
	
	bt 	查看当前程序函数栈帧使用基本情况

		函数的栈帧保存局部变量和临时值，形参，与局部变量等价。
	
	info locals 查看当前栈帧上变量的存储值。
	
	frame 栈帧编号查看变量的值
	
	s——step
	n——next

	finish 终止当前函数

	continue 结束当前断点调试
	
	p *数组名@10 列出数组前10个元素值

	p 数组名[n]@m 从下标n开始向后打印m个元素。

-----------------------------------------

静态模式规则:

ALL：$(target)

$(target):%.o:%.c
	gcc -c xxxx -o xxxx






















