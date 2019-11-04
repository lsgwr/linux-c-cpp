# Linux文件操作

## man命令的使用

### 英文版

+ 1、 Executable programs or shell commands
+ 2、 System calls (functions provided by the kernel)
+ 3、 Library calls (functions within program libraries)
+ 4、 Special files (usually found in /dev)
+ 5、 File formats and conventions eg /etc/passwd
+ 6、 Games
+ 7、 Miscellaneous (including macro packages and conventions), e.g. man(7), groff(7)
+ 8、 System administration commands (usually only for root)
+ 9、Kernel routines [Non standard]


### 中文版

+ 1、是普通的命令
+ 2、是系统调用,如open,write之类的(通过这个，至少可以很方便的查到调用这个函数，需要加什么头文件)
+ 3、是库函数,如printf,fread
+ 4、是特殊文件,也就是/dev下的各种设备文件
+ 5、是指文件的格式,比如passwd,就会说明这个文件中各个字段的含义
+ 6、是给游戏留的,由各个游戏自己定义
+ 7、是附件还有一些变量,比如向environ这种全局变量在这里就有说明
+ 8、是系统管理用的命令,这些命令只能由root使用,如ifconfig

### 使用例子

<p>在shell中输入man+数字+命令/函数即可以查到相关的命令和函数。若不加数字，那Linux man命令默认从数字较小的手册中寻找相关命令和函数。

例 如：我们输入man ls，它会在最左上角显示“LS（1）”，在这里，“LS”表示手册名称，而“（1）”表示该手册位于第一节章，同样，我们输入“man ifconfig”它会在最左上角显示“IFCONFIG（8）”。也可以这样输入命令：“man [章节号]手册名称”。

man是按照手册的章节号的顺序进行搜索的，比如：man sleep，只会显示sleep命令的手册,如果想查看库函数sleep，就要输入：man 3 sleep
</p>