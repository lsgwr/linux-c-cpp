# ubuntu（Linux）下的GCC编译器集合
  > ubuntu的GCC编译器集合，在安装ubuntu时就自带了，实际上和codeblocks安装目录MingW目录下的GCC编译器集合一样，都是GNU组织开发的，只不过codeblocks这边是面向windows的，而ubuntu这边的GCC是面向Linux的。
      
  注意区分大写的GCC和小写的gcc。<br/>
  **GCC**：指编译器集合<br/>
  **gcc**：指集合中的gcc程序<br/>

  正是由于都是由GNU开发的，所以集合中的程序名字是一样的，有了前面codeblocks GCC的基础，ubuntu的GCC非常容易。
			

## 编译时必须用到的基本程序**cpp、cc1、as、collect2/ld、gcc**
							
### 1）cpp（/usr/bin/）：预编译
  通过which可以查看cpp的安装目录。				
 + （a）man手册查看
 + （b）演示<br/>
        `cpp helloword.c -o helloword.i`<br/>
        不指定目标文件，会直接将预处理后的结果输出到控制台（命令行）。
		
								
### 2）cc1（/usr/lib/gcc/x86_64-linux-gnu/5/cc1）：编译
  无法通过which查看cc1的安装目录，因为cc1的安装目录没有加入环境变量。

   + （a）man手册查看<br/>
        查看不了，因为安装没有cc1的手册

   + （b）演示<br/>
        `/usr/lib/gcc/x86_64-linux-gnu/5/cc1 helloword.i -o helloword.s`

   + （c） 为什么要加路径？<br/>
        因为cc1所在的路径，没有加入Linux的环境变量。
							
								
### 3）as（/usr/bin/as）：汇编编译
  + （a）man  as

  + （b）演示<br/>
        
       `as helloword.s -o helloword.o`

      不指定目标文件，会自动保存到同名的目标文件。
							
							
### 4）collect2/ld：链接
+ ld路径：`/usr/bin/ld`
+ collect2：`/usr/lib/gcc/x86_64-linux-gnu/5/collect2`

同样的，如果直接使用collect2/ld来链接的话，我们需要自己指定很多的选项和参数，所以我们一般不自己
调用collect2/ld来链接，而是使用gcc来链接（gcc自动调用collect2/ld）。

`gcc helloword.o -o helloword`

不指定可执行文件的名字，就默认为a.out。

不要以为默认的名字时a.out，就认为Linux可执行文件的尾缀是.out，Linux下的可执行文件并没有尾缀要求。

我们后面会介绍默认的a.out这个名字是怎么来的。
							
							
### 5）gcc
使用gcc这个总的调度程序，gcc会自动调用cpp、cc1、as、collect2/ld等程序。  
可以避免直接使用cpp、cc1、as、collect2/ld等程序所带来的麻烦。下面是常用的gcc的参数

+ -E
  + 只得到.i扩展c源文件

    `gcc -E helloworld.c -o helloworld.i`

  + 如果不写目标文件，就直接输出到控制台。

  + file查看.i文件类型


+ -S	
  + 只编译到.s文件

  + 演示
    `gcc -S helloworld.i -o helloworld.s`
    `gcc -S helloworld.c -o helloworld.s`

    同样的，如果不写目标文件，会自动保存为同名的.s文件

  + file查看.s文件类型

+ -c	
  + 只编译得到.o文件

  + 演示
    汇编文件生成.o文件 :`gcc -c helloworld.s -o helloworld.o`  
    预编译文件生成.o文件：`gcc -c helloworld.i -o helloworld.o`  
    源码文件生成.o文件`：gcc -c helloworld.c -o helloworld.o`  

    如果不写目标文件，会自动的保存为同名的.o文件

  + file查看.o文件类型`file 文件名`


+ 直接得到可执行文件

  + 演示  
    `gcc helloworld.c -o helloworld`  
    `gcc helloworld.i -o helloworld`  
    `gcc helloworld.s -o helloworld`  
    `gcc helloworld.o -o helloworld`  

  + 如果不写可执行文件，会自动保存为a.out文件。

  + file查看可执行文件类型

+ 其它选项：O1、O2、Os、O3、Wall、g等选项
    与前面介绍的是一样的。

							
## 编译器集合中的其它程序：nm、strip、objdump、ar、readelf、debug
> 这程序都在/usr/bin/目录下，可以使用witch命令查看所在的目录。
								
+ 1）nm：查看.o、可执行文件中的各种符号  
  演示：  
    `nm helloworld.o`  
    `nm helloworld`

+ 2）strip：对可执行文件进行瘦身
    给gcc指定-s选项时，gcc就是调用strip来瘦身的。  
    我们也可以gcc时先不指定-s，然后自己主动使用命令`strip 可执行结果文件`来瘦身。  

+ 3）objdump：反汇编，将机器指令反翻译为可以被人识别的汇编指令，这就反汇编
  + 演示  
    - 对.o文件进行反汇编
      objdump -D hellowolrd.o >  hw1.s

      `>`：将反汇编结果保存到dmphelloworld1.s中。

    - 对可执行文件进行反汇编
      objdump -D hellowolrd > dmphelloworld2.s


  + 反汇编的意义
      其实对于做应用程序开发的我们来说，反汇编的意义不大，但是对于做逆向开发的人来说，这就很有意义，因为做逆向开发的人，需要分析二进制的机器指令，  
      但是纯二进制的机器指令很难阅读，所以必须将二进制机器指令反翻译为ascii的汇编指令，才能阅读。  
      不知道什么是逆向开发的同学，请看《计算机体系结构——行业篇》的内容。  

  + 介绍objdump的目的。
    - 有必要了解
    - 本章后面可能会用到
    - 后续可能会出逆向的课，到时候就会用到反汇编命令


+ 4）ar：用来制作静态库文件，讲c函数库时再介绍。


+ 5）readelf：读取elf格式信息
    后面用到时在介绍。

+ 6）debug
    调试程序用的，后面课程介绍。
