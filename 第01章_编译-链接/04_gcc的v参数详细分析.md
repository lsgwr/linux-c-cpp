# gcc xxx.c -o xxx.out *-v*的详细分析
> 这里的-v是用于显示编译过程中的详细信息的

## 演示
  `gcc helloword.c -o helloworld -v`  
  下面代码中红色的是我自己添加的注释，其他的都是上面命令产生的回显，为了方便看很多地方换行了
  ```shell
  Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/4.8/lto-wrapper
Target: x86_64-linux-gnu

/**********************************************gcc配置信息*****************************************************/
Configured with: ../src/configure /**gcc的配置文件路径，常用于大型工程的代码条件编译**/
-v --with-pkgversion='Ubuntu 4.8.4-2ubuntu1~14.04.3'
--with-bugurl=file:///usr/share/doc/gcc-4.8/README.Bugs /**如果发现的gcc的bug需要按照README.bufs说明书的内容来提交bug**/
--enable-languages=c,c++,java,go,d,fortran,objc,obj-c++ /**gcc编译集所支持的语言**/
--prefix=/usr /**路径固定前缀，也就是说gcc所用的路径都是以/usr开头地，换句话说gcc所用到的文件都在/usr目录下**/
--program-suffix=-4.8 
--enable-shared 
--enable-linker-build-id 
--libexecdir=/usr/lib 
--without-included-gettext 
--enable-threads=posix 
--with-gxx-include-dir=/usr/include/c++/4.8 
--libdir=/usr/lib /**GCC编译器集合自带库所在目录**/
--enable-nls 
--with-sysroot=/ 
--enable-clocale=gnu 
--enable-libstdcxx-debug 
--enable-libstdcxx-time=yes 
--enable-gnu-unique-object 
--disable-libmudflap 
--enable-plugin 
--with-system-zlib 
--disable-browser-plugin
/**使用gcc编译带界面的java程序，图形界面底层调用地是ubuntu的gtk基础图形库，下面两行都是**/
--enable-java-awt=gtk 
--enable-gtk-cairo 
/**gcc编译java需要的运行环境配置信息，下面7行到--enable-objc-gc都是**/
--with-java-home=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64/jre 
--enable-java-home 
--with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64 
--with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-4.8-amd64 
--with-arch-directory=amd64 
--with-ecj-jar=/usr/share/java/eclipse-ecj.jar 
--enable-objc-gc 
/**gcc所运行的cpu的结构，对于cpu结构的详细信息，作为应用开发者只需要简单了解，但是对于做硬件、微电子、编译器开发的需要详细了解，下面8行都是**/
--enable-multiarch 
--disable-werror 
--with-arch-32=i686 
--with-abi=m64 
--with-multilib-list=m32,m64,mx32 
--with-tune=generic 
--enable-checking=release 
--build=x86_64-linux-gnu 
/**gcc本身的运行环境：cpu是64位的intel x86 cpi 操作系统是linux**/
--host=x86_64-linux-gnu 
/*gcc编译出的可执行程序的运行环境*/
--target=x86_64-linux-gnu

/*******************************************gcc的其他信息****************************************************/
Thread model: posix
/**gcc版本，与gcc所运行的ubuntu的版本(Linux发行版操作系统)**/
gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.3) 
/**gcc的基本选项，-march=x86-64表示为intell 64位 x86的cpu; -mtune=generic表示编译得到机器指令时，机器指令属于通用指令集，
即不同版本x86和cpu都支持的指令集，如果需要指定某款cpu的特殊指令集时，就不能是generic，需要写成其他名称**/
COLLECT_GCC_OPTIONS='-o' 'helloworld' '-v' '-mtune=generic' '-march=x86-64'
/** 第1、2步：预编译+编译,下面3行，核心是 cc1 helloworld.c -o /tmp/cc2SMRPO.s **/
 /usr/lib/gcc/x86_64-linux-gnu/4.8/cc1 -quiet -v -imultiarch x86_64-linux-gnu helloworld.c
 -quiet -dumpbase helloworld.c -mtune=generic -march=x86-64 -auxbase helloworld
 -version -fstack-protector -Wformat -Wformat-security -o /tmp/cc2SMRPO.s
/**下面4行忽略 **/
GNU C (Ubuntu 4.8.4-2ubuntu1~14.04.3) version 4.8.4 (x86_64-linux-gnu)
        compiled by GNU C version 4.8.4, GMP version 5.1.3, MPFR version 3.1.2-p3, MPC version 1.0.1
GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
ignoring nonexistent directory "/usr/local/include/x86_64-linux-gnu"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../x86_64-linux-gnu/include"
/**包含""所指定的头文件：到程序员自己指定的路径下去找**/
#include "..." search starts here:
/**包含<>所指定的文件：到下面的指定的路径下去找**/
#include <...> search starts here:
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include
 /usr/local/include
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.
/**下面5行忽略 **/
GNU C (Ubuntu 4.8.4-2ubuntu1~14.04.3) version 4.8.4 (x86_64-linux-gnu)
        compiled by GNU C version 4.8.4, GMP version 5.1.3, MPFR version 3.1.2-p3, MPC version 1.0.1
GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: a0a649d344b1ed798e33d30772d46437
COLLECT_GCC_OPTIONS='-o' 'helloworld' '-v' '-mtune=generic' '-march=x86-64'
/**第3步：汇编， as已经加到环境变量所以无需指定绝对路径**/
 as -v --64 -o /tmp/ccujC6sr.o /tmp/cc2SMRPO.s
GNU assembler version 2.24 (x86_64-linux-gnu) using BFD version (GNU Binutils for Ubuntu) 2.24
COMPILER_PATH=/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/
LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-o' 'helloworld' '-v' '-mtune=generic' '-march=x86-64'
/**第4步：链接**/
 /usr/lib/gcc/x86_64-linux-gnu/4.8/collect2 /**链接器所在的路径，因为collect2没有加入环境变量，所以需要自己指明**/
 --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed  -z relro /**各种选项和参数，不需要了解**/
 -dynamic-linker /lib64/ld-linux-x86-64.so.2 /**给程序指定动态加载器：程序运行起来后，用于加载动态库**/
 -o helloworld /**最终生成的可执行文件**/
 /**下面3行是用于生成程序的"启动代码(搭建C/C++运行环境)"，这三个.o是由GCC编译器集合提供的(由GCC开发者编写)，crt=c++ run time=运行时环境，
 /**crt1.o: 汇编写的，里面的_start是整个程序的开始；调用main函数;建立c函数运行所需要的栈**/
 /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crt1.o 
 /**crti.o: 在调用main函数之前，实现c的一些初始化工作，比如全局变量的初始化**/
 /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crti.o
 /**在调用main之前，实现c++的一些初始化工作，比如全局构造函数、创建全局对象等**/
 /usr/lib/gcc/x86_64-linux-gnu/4.8/crtbegin.o
 /**下面8行指定所有库所在路径，后面链接`库`时就到这些路径下寻找，后面讲C函数时，会介绍-L选项(L是Library的意思)**/
 -L/usr/lib/gcc/x86_64-linux-gnu/4.8
 -L/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu 
 -L/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../lib 
 -L/lib/x86_64-linux-gnu 
 -L/lib/../lib 
 -L/usr/lib/x86_64-linux-gnu 
 -L/usr/lib/../lib 
 -L/usr/lib/gcc/x86_64-linux-gnu/4.8/../../.. 
 /**链接自己的代码生成的.o文件，这个是前面第3步as汇编helloworld.c时所得到的.o文件**/
 /tmp/ccujC6sr.o /**我们源文件只有一个helloworld.c，所以只有一个.o，源文件有多个时，就会有读个.o**/
 /**忽略**/
 -lgcc --as-needed -lgcc_s --no-as-needed
 /**链接libc库(C标准函数库)
  其实libc只是c标准函数库中的一个子库，libc只包含printf、scanf、strcpy、malloc、time等这些常用函数，
  正是因为gcc有自动链接libc这个常用函数库，所以我们才能在程序中使用这些常用函数，而不会报错说倒找
  不到这些函数。

  但是像c标准函数库中的其它函数就不行了，比如使用数学函数，我们必须自己在gcc时自己加-lm去链接
  c标准函数库的子库——数学库（比如：gcc ***.c -o *** -lm）， 
  否者无法使用数学库函数，数学库中的函数属于非常用函数，gcc是不会帮你自动链接数学库的。
  **/
 -lc 
 /**忽略**/
 -lgcc --as-needed -lgcc_s --no-as-needed
 /**下面两行是扫尾代码
 用于生成扫尾代码，程序运行结束时，做一些扫尾工作，这两个.o也是由gcc
 开发者编写的，为了方便描述，我们往往将扫尾代码认为是启动代码的一部分。
      crtend.o：扫尾做什么？比如调用c++析构函数，释放全局对象的空间
      crtn.o：扫尾做什么？比如，接收main函数的返回值并处理
        - 如果程序是裸机运行的，返回值到扫尾代码这里就结束了，裸机时返回值的意义不大
        - 如果程序是基于OS运行的，扫尾代码会将返回值交给OS				
 **/
 /usr/lib/gcc/x86_64-linux-gnu/4.8/crtend.o
 /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crtn.o
  ```

## 分析gcc -v的详细信息的意义

  首先我们需要清楚一点，我们并不能完全弄清楚gcc -v的所有信息，因为毕竟我们并不是GCC编译器集合的
实现者，对于这些信息，他们才是最清楚的。  

  由于我们不能将所有的信息都搞清楚，所以我们只分析关键信息。  

  虽然我们不能将所有信息都全部弄清楚，但是分析里面的关键信息还是非常有意义的，我们可以通过这些信息
弄清楚很多事情，比如：  

+ 通过这些信息，我就知道gcc其实最终还是调用cc1/as/collect2等程序来实现编译的四个过程的。
+ 知道c的启动代码是怎么来的
+ 知道为什么在程序中调用printf、scanf、malloc等函数时，我们不需要主动链接这些函数的动态库，但是依然
  能够使用这些函数


## `gcc helloword.c -o helloworld -v`详细信息分析

  `Using built-in specs.` //编译链接详细信息  
  `COLLECT_GCC=gcc`  			//编译时所调用的总调度程序  

  gcc编译得到的可执行文件的运行环境:
  cpu：64位x86， OS：linux， gnu：gcc的开发组织  
  Target: x86_64-linux-gnu  


## gcc配置信息：

### 1. 什么是gcc配置信息
        gcc也是一个程序，也是被别人开发出来的，应该是c/c++语言写的。

        编写gcc这个编译器程序的人，在编译gcc时所给的信息就是配置信息，这些信息会决定编译gcc哪些代码，
      不编译哪些代码，最终得到针对某个环境（OS/CPU）的gcc可执行程序。

### 2. gcc程序如何面对众多环境的
        gnu开发的gcc可以面对很多的环境，比如windows x86环境，Linux x86环境，Linux arm环境。

        编写gcc的人，为了让程序能够应对各种环境（OS、cpu），gcc程序里面会包含应对各个环境的代码，
      如果你想得到针对某个环境gcc可执行程序，就必须只编译针对该环境的代码，其它代码不编译。


### 3. 如何选择只编译gcc程序针对某个环境的代码

        通过条件编译来选择，通过条件编译这的东西，就可以在预编译阶段决定你要保留哪些代码，放弃哪些代码，
      编译时只编译你保留的代码。

        举一个简单的例子
        比如：

        gcc.c

        #define X86_LINUX


        #ifdef X86_LINUX
        针对x86、Linux环境的代码。
        #endif


        #ifdef ARM_LINUX
        针对arm、Linux环境的代码。
        #endif


        #ifdef X86_WINDOWS
        针对X86、windows环境的代码。
        #endif

        通过条件编译所需的宏，就能让条件编译保留和编译只针对某个环境的代码。


          但是由于c条件编译使用的宏实在是太多了，所以我们不可能自己一个一个的定义这些宏，所以就需要
        通过配置信息自动生成需要的宏。

          配置信息保存在哪里呢？
          配置信息保存在配置文件中，我们配置信息时，其实就是修改配置文件中的内容。

          运行配置文件时，根据配置信息的要求，会自动生成需要的宏定义，并把这些宏定义保存到相应
        的.h（头文件）中。

          再将.h给c/c++程序，预处理时，条件编译根据.h中定义的宏定义，就能决定保留和编译哪些代码。
          编译时就只编译保留的代码，最后就得到了针对某个环境的gcc可执行程序，不过这些配置信息会保留
        gcc中，gcc -v时会显示出来。

          通过了解gcc的配置信息，可以大概的知道一些gcc的特性。


### 4. 了解gcc 条件编译和配置信息 的意义

      （1）有助于我们后面学习c语言"条件编译"相关的内容

      （2）复杂的c/c++程序，都会涉及到条件编译和配置信息
          gcc也是一个复杂的c/c++程序，所以必然涉及条件编译和配置信息。

          如果不理解条件编译和配置信息的话，我们很难实现复杂c程序和看懂别人写的复杂c程序。

          我们后面讲uboot和linux内核时，里面会有大量的条件编译，编译时必须修改配置信息，通过配置信息
        去打开和关闭uboot/linux内核的条件编译，选择那些代码保留，那些代码忽略，然后编译保留的代码，
        得到针对某个环境（OS/CPU）的可执行程序。



### 5. gcc配置信息
      gcc的配置文件，这句话仅仅只是向我们表明，gcc的配置信息其实是来源于这个文件，这个配置文件并不在
      我的电脑上，而是在gcc开发者的电脑上，编译gcc时gcc开发者会去设置这个配置文件。
      Configured with: ../src/configure 


      gcc bug报告说明书：如果你发现了gcc的bug，需要按照README.Bugs说明书的要求来提交gcc的bug
      --with-bugurl=file:///usr/share/doc/gcc-5/README.Bugs 


      gcc编译器集合所支持的语言，不过想要编译java等其它语言，需要下载相应的插件
      --enable-languages=c,ada,c++,java,go,d,fortran,objc,obj-c++ 		

      路径固定前缀，也就是说gcc所使用到的路径都是/usr打头的，换句话说gcc所
      用到的文件，都在这个/usr目录下。
      --prefix=/usr 

      ....

      GCC编译器集合“自带库”所在目录
      --libdir=/usr/lib 

      ...

      使用gcc编译带界面的java程序，图形界面底层调用的是ubuntu的gtk基础图形库
      --enable-java-awt=gtk  


      gcc可以编译java，但是java程序运行需要相应的运行环境（最起码要有个java虚拟机jvm）
      以下信息描述的就是java的运行环境
      --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-5-amd64/jre 
      --enable-java-home 
      --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-5-amd64 
      --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-5-amd64 
      --with-arch-directory=amd64 
      --with-ecj-jar=/usr/share/java/eclipse-ecj.jar 
      --enable-objc-gc 


      gcc所运行的cpu的cpu架构，对于cpu架构的详细信息，对于应用开发者来说，我们不需要进行详细的了解
      这些是做硬件、微电子、编译器开发者应该详细了解的内容
      --enable-multiarch 
      --disable-werror 
      --with-arch-32=i686 
      --with-abi=m64 
      --with-multilib-list=m32,m64,mx32 
      --enable-multilib 
      --with-tune=generic									
      --enable-checking=release
      --build=x86_64-linux-gnu 


      //gcc本身的运行环境：cpu：64位intel X86 cpu  OS：Linux 
      --host=x86_64-linux-gnu  

      gcc编译出的可执行程的运行环境
      gcc helloworld.c -o helloworld，helloworld的运行环境为cpu：64位intel X86 cpu  OS：Linux 
      --target=x86_64-linux-gnu 



    --------------------------------------------------------------

      gcc版本，与gcc所运行的ubuntu的版本（ubuntu是Linux发行版操作系统）
      gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9) 


      gcc基本选项，
      -march=x86-64：intel 64位 x86 cpu
      -mtune=generic：编译得到的机器指令，属于通用指令集（同款的不同型号的cpu都支持的指令集）
        如果需要指定某型号cpu的特殊指令集时，就不能写成generic，而要写特殊指令集名称
      COLLECT_GCC_OPTIONS='-o' 'helloworld' '-v' '-mtune=generic' '-march=x86-64'


      预编译、编译
      干货信息为：cc1 helloworld.c -o /tmp/ccV9xVOr.s
      /usr/lib/gcc/x86_64-linux-gnu/5/cc1 -quiet -v -imultiarch x86_64-linux-gnu 
      helloworld.c -quiet -dumpbase helloworld.c -mtune=generic -march=x86-64 -auxbase 
      helloworld -version -fstack-protector-strong -Wformat -Wformat-security -o 
      /tmp/ccV9xVOr.s

      ... 



      包含""所指定的头文件：到程序员自己指定的路径下去搜索
      #include "..." search starts here:


      包含<>所指定的头文件：到系统指定的路径下去找
      #include <...> search starts here: 
      /usr/lib/gcc/x86_64-linux-gnu/5/include
      /usr/local/include
      /usr/lib/gcc/x86_64-linux-gnu/5/include-fixed
      /usr/include/x86_64-linux-gnu
      /usr/include
      End of search list.


      ... 


      汇编：由于as的路径已经被加入到了环境变量中，因此调用as时，并不需要指定as的路径。
      生成ccV9xVOr.s汇编文件是一个临时文件，/tmp目录专门用于存放Linux系统所生成的临时文件，
      一旦编译得到了可执行文件，这个ccV9xVOr.s将会别删除
      as -v --64 -o /tmp/ccyIcm4A.o /tmp/ccV9xVOr.s


      ...




      链接
      collect2为链接器，由于collect2的路径没有加入环境变量，因此需要我们自己指明
      collect2所在的路径。
      /usr/lib/gcc/x86_64-linux-gnu/5/collect2


      collect2的选项和参数
      ...

      给程序指定动态链接器：程序运行起来后，用于加载动态库
      -dynamic-linker /lib64/ld-linux-x86-64.so.2 

      ...

      最终生成的可执行文件
      -o helloworld 


      crt1.o、crti.o、crtbegin.o：用于生成程序的“启动代码”，这三个.o是由GCC编译器集合提供的
      （由GCC开发者编写的），crt就是c/c++ run time的意思，翻译为中文就是“运行时环境”。

        启动代码的作用：搭建c/c++的运行环境

        crt1.o：汇编写的。
        · 里面的_start是整个程序的开始（入口）
        · main函数是由crt1.o调用
        · c/c++函数运行所需要的栈，是由crt1.o建立的
        crti.o：在调用main之前，实现c的一些初始化工作，比如全局变量初始化
        crtbegin.o：在调用main之前，实现c++的一些初始化，比如调用全局构造函数，创建全局对象
      /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o 
      /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crti.o 
      /usr/lib/gcc/x86_64-linux-gnu/5/crtbegin.o 




      指定所有库所在路径，后面链接“库”时就到这些路径下寻找，后面讲c函数库时，会介绍-L选项
      -L/usr/lib/gcc/x86_64-linux-gnu/5 
      -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu 
      -L/usr/lib/gcc/x86_64-linux-gnu/5/../../../../lib 
      -L/lib/x86_64-linux-gnu -L/lib/../lib 
      -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib 
      -L/usr/lib/gcc/x86_64-linux-gnu/5/../../.. 


      链接自己的.o：ccyIcm4A.o，是之前as汇编helloworld.c时，所得到的临时.o文件
      我们这里自己的.o只有一个，如果源文件有很多.c的话，对应的这里就会有很多的.o
      /tmp/ccyIcm4A.o

      ...


      链接libc库
      其实libc只是c标准函数库中的一个子库，libc只包含printf、scanf、strcpy、malloc、time等这些常用函数，
      正是因为gcc有自动链接libc这个常用函数库，所以我们才能在程序中使用这些常用函数，而不会报错说倒找
      不到这些函数。

      但是像c标准函数库中的其它函数就不行了，比如使用数学函数，我们必须自己在gcc时自己加-lm去链接
      c标准函数库的子库——数学库（比如：gcc ***.c -o *** -lm）， 
      否者无法使用数学库函数，数学库中的函数属于非常用函数，gcc是不会帮你自动链接数学库的。
      -lc 

      ...



      crtend.o、crtn.o：用于生成扫尾代码，程序运行结束时，做一些扫尾工作，这两个.o也是由gcc
        开发者编写的，为了方便描述，我们往往将扫尾代码认为是启动代码的一部分。

      crtend.o：扫尾做什么？比如调用c++析构函数，释放全局对象的空间
      crtn.o：扫尾做什么？比如，接收main函数的返回值并处理
        - 如果程序是裸机运行的，返回值到扫尾代码这里就结束了，裸机时返回值的意义不大
        - 如果程序是基于OS运行的，扫尾代码会将返回值交给OS									
      /usr/lib/gcc/x86_64-linux-gnu/5/crtend.o 
      /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crtn.o




      /* 简化后的链接过程，链接时，各个模块的顺序很重要 */
      collect2    //链接程序

      -dynamic-linker  /lib64/ld-linux-x86-64.so.2 //动态链接器

      crt1.o  crti.o  crtbegin.o  //启动代码

      ccyIcm4A.o  								//自己程序的.o，这里目前只有一个

      -lc 												//libc，常用c函数库——c标准库的子库

      crtend.o  crtn.o 						//扫尾代码



### 6.总结gcc -v显示的详细信息

    （1）如果四个过程都有的话
          详细信息就是：gcc配置信息 + cc1信息(预处理+编译) + as信息 + collect2信息 

    （2）如果只是某个过程的话
         比如：gcc -S helloworld.i -o helloworld.s -v

         详细信息就是：gcc配置信息 + 单个过程的信息



### 7. 再说说启动代码 
  （1）启动代码是由“一个汇编文件+其它的.c文件”构成的，启动代码并不是我们程序员写的
      · 广义上，“汇编文件+其它的.c文件”都是启动代码。

      · 狭义上，“汇编文件”才是启动代码


  （2）启动代码的作用
      其中的核心作用就是，在内存中建立c程序运行所需的“堆和栈”，堆和栈其实就是程序运行时所需的运行环境之一，
    所谓运行环境，就是程序运行时必须要的支撑，就跟人一样，人活着也需要环境（生活环境/工作环境）的支撑，
    否则就麻烦了。

      程序运行起来后就变成了动态运行的程序——进程，所以程序的运行环境，也被称为“进程环境”，进程环境不仅仅
    只有“堆和栈”，还需要其它的，我们在《Linux系统编程/网络编程》第4章，将会详细的介绍什么“进程环境”，
    所以需环境有哪些。


  （3）我想看启动代码的源码，怎么办？
        如果想看启动代码的话，也主要是汇编部分，因为.c部分，会根据程序运行时有无OS支持，会有很大的区别。

        比如单片机没有OS，它的启动代码.c部分与有OS时启动代码的.c部分有很大区别，不仅.c，汇编部分也有
      区别，只不过区别没有那么大而已。

        .c部分我们就不关心了，如果你想看启动代码汇编部分，完全可以看单片机c程序的启动代码汇编部分。


        当有OS支持时，编译器提供的启动代码大都会被做成现成的.o，我们是看不到源码的，基本只有在裸
      机程序中才能看到启动代码汇编部分的源码，.c源码也能看见。

        所谓裸机程序就是没有OS支持的程序，比如绝大多数单片机程序就是典型的裸机程序，为什么呢？
      因为单片机很少运行OS，由于单片机开发的特殊性，有时候我们往往需要修改启动代码汇编部分，所以编译器
      会提供汇编启动代码的源码，所以完全可以通过看单片机的汇编启动代码，从而了解C的汇编启动代码干了什么
      事情。

        在有OS支持时，启动代码是不需要修改的，所以人家才以.o心事提供。


        讲单片机时，我们会分析单片机c程序的汇编启动代码，所以到时候你就知道它到底做了些什么事情，它是
      怎么去建立堆和栈的，建立堆和栈的代码长什么样子，那时你就不会再对启动代码感到神秘了。

        图：大概看看单片机的汇编启动代码长什么样子

          ...
          /* 设置堆栈指针，堆栈的大小 */
          Stack_Size      EQU     0x00000400

          AREA    STACK, NOINIT, READWRITE, ALIGN=3
          Stack_Mem       SPACE   Stack_Size
          __initial_sp


          ; <h> Heap Configuration
          ;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
          ; </h>

          Heap_Size       EQU     0x00000200

                          AREA    HEAP, NOINIT, READWRITE, ALIGN=3
          __heap_base
          Heap_Mem        SPACE   Heap_Size
          __heap_limit

                          PRESERVE8
                          THUMB

          ...


        当然后续课程讲Uboot移植时，由于Uboot也是一个裸机程序，我们也能够看到Uboot的汇编启动代码
      的源码，你也能知道启动代码到底做了些什么事情，总之对于启动代码不要感到神秘，也没什么可神秘的。

        不仅c程序，所有高级语言所写的程序，都是需要启动代码的，启动代码要做的事情也都是类似的。

        当然就算你不了解启代码是咋回事，对于我们开发来说，也不会有什么太大的问题，但是如果你能了解什么
      是启动代码，大概做了些什么事情，当然是最好的了，因为这非常有助于你去理解与之相关的一些其它的深
      入问题。
