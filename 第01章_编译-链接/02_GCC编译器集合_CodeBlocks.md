# codeblocks的编译器集合
> 编译器并不是一个单独的程序，而是一堆程序的集合。

## codeblocks安装目录
  CodeBlocks的安装包版本为codeblocks-17.12mingw-setup.exe,去http://www.codeblocks.org/downloads/26 下载，版本号酌情选取，不过最好选则自带MinGW编译器的。<br/>
  去codeblocks的编译器集合就放在它的安装目录下(MinGW),比如我的是`D:\Program Files (x86)\CodeBlocks`,MinGW的目录为`D:\Program Files (x86)\CodeBlocks\MinGW`
									
## 编译的四个过程，必须用到的基本程序
   **cpp、cc1、as、collect2/ld、gcc** <br/>
   gcc编译时四个过程自动完成，我们既然已经知道了这四个过程，那么我们就自己一步一步实现这四个过程，然后得到最终的可执行文件。<br/>
   我们讲这四个过程的主要目的是什么呢？<br/>
      · 熟悉这四个编译过程，了解每个过程做了什么事<br/>
      · 了解每个过程调用了编译器集合中什么程序<br/>

   疑问：老师，你怎么知道编译四过程使用的就是cpp、cc1、as、collect2、gcc这些程序呢？<br/>
   我们后面再来回答这个问题。
							
### 1）cpp `MingW\bin\cpp.exe`

+ （a）预编译程序（预编译器、预处理器）：实现预编译 <br/>
    为了方便我们查看预编译后的结果，我们先在.c中加入宏、条件编译、头文件包含。

+ （b）演示<br/>

    `cpp helloworld.c -o helloworld.i`<br/>
    
    - o选项用于指定目标文件，表示将预处理后的结果保存到.i文件中。
    - 验证.i文件是不是ascii文件。

    - 验证预处理后.c中的宏、include、条件编译，在.i中还能否见到。
									
									
### 2）cc1 `MingW\libexec\gcc\mingw32\5.1.0\cc1.exe`

  + （a）编译程序（编译器）：将C源码翻译为汇编源码

  + （b）演示
      
       `..\libexec\gcc\mingw32\5.1.0\cc1 helloworld.i -o helloworld.s`<br/>
    
    验证.s文件是不是ASCII文件。


  + （c）cc1值得注意的地方
  
      其实cc1本身也包含cpp预处理的功能，也就是说可以直接使用cc1将.c——>.s，cc1会完成之前的预处理的功能。<br/>
					`..\libexec\gcc\mingw32\5.1.0\cc1 helloworld.c -o helloworld.s`<br/>
			不过以上命令并不能被成功执行，因为还缺参数，他会提示找不到头文件，至于缺什么参数，我们这里就不关心了。
									
									
									
### 3）as `MingW\bin\as.exe`
  + （a）汇编程序（汇编器）：将汇编源码翻译为纯二进制的机器指令，放到.o文件中

  + （b）演示<br/>
        `as helloworld.s -o helloworld.o`
									
									
### 4）ld、collect2 <br/>
      
ld路径：`MingW\bin\ld.exe`、`MinGW\mingw32\bin\ld.exe` 
collect2路径：`MingW\libexec\gcc\mingw32\4.9.2\collect2`

  + （a）链接程序（链接器（静态链接器））
        将所有的.o文件（自己的、编译器提供的）和库（动态库、静态库）链接在一起，得到可以运行的可执行文件。

  + （b）collect2 和 ld之间的关系
      collect2是对ld进一步封装得到的，这两个都可以用于链接。

  + （c）演示 <br/>
  
      实际上我们完全可以自己调用collect2和ld这两个程序（命令）来进行链接，但是链接并不是一件容易的事情，链接的时候需要跟大量的参数和选项，这些参数和选项我们自己并不清楚，所以我们自己调用collect2 和 ld来链接的话，实际上操作起来比较困难。<br/>
      所以链接的话，我们直接使用gcc程序来链接，gcc会自动调用collect2或者ld来链接，并且自动指定需要的各种的选项和参数，我们并不是需要关心。<br/>
      
	`gcc helloworld.o -o helloworld`<br/>

	或者<br/>

	`gcc helloworld.o`  <br/>
      _如果不指定可执行文件名字的话，默认为a.exe_
									
														
### 5）gcc、mingW32-gcc、g++、c++  均在`MinGW/bin`目录下

  > 其实gcc、mingW32-gcc、g++这几个都能编译c程序。

+ （a）gcc、mingW32-gcc、g++的关系

	其中mingW32-gcc是对gcc继续做封装后得到的。<br/>
	c++/g++是用来编译c++程序的，但是由于c++程序兼容c，所以c++/g++也能编译c程序。<br/>
	正式因为编译集合中包含了g++，所以我们也能使用codeblocks来写c++程序的，而且codeblocks这个IDE本身好像就是c++写的。

+ （b）gcc、mingW32-gcc、g++程序的作用

      gcc/mingW32-gcc/g++/c++其实是总的调度程序，它按照需求去调用cpp/cc1/as/collect2/ld等程序，
    完成对应四个过程。	<br/>

    为什么要一个总的调度程序？<br/>
      通过前面的讲解知道，虽然我们能够自己调用cpp/cc1/as/collect2/ld来完成四个过程，得到最后的可执行文件，但是存在如下缺点。<br/>

    - 每个阶段的程序名都不一样，不方便记忆<br/>
        第一阶段叫cpp，第二阶段叫cc1等，老实讲，时间久了我也忘了。<br/>
        有了gcc这个总调度程序后，不管是哪个阶段，对于我们来说，只需要记住gcc这一个程序即可。<br/>
        你想实现那个阶段，通过gcc即可实现，通过给gcc指定不同的选项，gcc可以自动调用cpp、cc1、as、collect2、ld中所需要的程序来实现对应的过程。

    - 如果每个阶段都我们自己亲自执行cpp/cc1/as/collect2/ld这些程序来编译的话，速度太慢了<br/>
        有了gcc后，虽然可以通过指定选项，分别实现每个过程，但是实际上也可以调用gcc一次性快速完成四个过程，gcc会自动调用cpp/cc1/as/collect2/ld来完成。<br/>
        一次性完成时，中间产生的.i/.s/.o都是临时文件，编译后会被自动删除，这些文件我们并不关心，我们关心的只是最后的可执行文件。<br/>
        使用gcc这个总调度程序，一次性完成所有过程时，编译速度非常快，用起来非常方便。<br/>
