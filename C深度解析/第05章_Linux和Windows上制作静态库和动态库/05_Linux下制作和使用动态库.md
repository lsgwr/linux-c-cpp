# 8.2.2 制作、使用动态库

## （1）编写制作为动态库的例子代码
我们任然还是前面制作静态库的代码。  
			
## （2）制作动态库文件	

### 1）得到.o文件 

```shell
gcc -c -fPIC add_sub.c -o add_sub.o 
gcc -c -fPIC mul_div.c -o mul_div.o 
```

+ -fPIC(for Position Independent Code)：生成位置无关码
    + **位置有关码**： 
    
      代码的地址为绝对地址，代码必须被放在绝对地址所指定的内存位置，这个绝对地址在编译链接时由编译器指定，如果不将代码放到指定位置，将无法正确运行。  
      
      这就好比两个人接头，指定说在“张家巷128号”接头，这个就是位置相关的，要是不到“张家巷128号”这个绝对位置去的话，两个人肯定碰不上面的。  
      
      所以对于位置有关的代码来说，必须运行在“编译链接”时指定地址的内存位置，否则无法正常运行。  
      
      总之，位置有关的代码依赖于编译链接时指定的地址，必须把代码放到地址所指向的内存空间，才能运行。  

   +  **位置无关码**：  
   
        代码与绝对地址没有关系，放到内存中任何地址的位置都可以正常运行，这就好比两个人接头时约定，双方以烟花为号，大家到放烟花的位置去集合，这就跟绝对地址无关，任何地方都可以碰头，就看烟花在哪里。  

        对于位置无关码来说，不管在代码在内存中什么位置，都可以正常运行，不依赖于编译链接时所指定的地址。  

        有关位置无关码的具体原理，请看后面uboot的课程，里面会详细介绍。  

    + **动态库的代码为什么需要是位置无关的？**  
    
        动态库被加载到内存什么位置是不确定的，可能会加载到任何位置，所以必须编译为位置无关码  
	
        总之，位置无关码的意思就是，代码不会受到内存位置的影响  

### 2）将.o文件打包为动态库文件

制作动态库的命令不再是ar，而是gcc，而且动态库文件不再是普通的归档文件。

```shell
gcc -shared add_sub.o  mul_div.o  -o  ./libmycaculate.so
```

+ （a）`-shared`：制作动态库  
+ （b）`./libmycaculate.so`：动态库的路径名   
        为了和前面介绍的静态库的名字进行区别，我们这里把动态库的名字取名为mycaculate  
+ （c）`add_sub.o` 、`mul_div.o`  
        制作动态库的原料  
	

执行命令完毕得到如下文件(not stripped代表可以用strip命令进行文件大小优化，见`第01章_编译-链接/03_GCC编译器集合_Ubuntu.md`)：

```shell
root@9e2614e43d08:/workspace/libmake# file libmycaculate.so 
libmycaculate.so: ELF 64-bit LSB  shared object, x86-64, version 1 (SYSV), dynamically linked, BuildID[sha1]=fb2600a51029ba06b799f11d0c31228ae2139cbb, not stripped
```
									
## （3）使用动态库文件

使用动态库有两步：  

+ 链接动态库  

+ 加载动态库到内存中  
    链接静态库时，代码会直接被包含到程序中，但是链接动态库时，代码并不会被直接包含到程序中，只是留了一个“函数接口”，所以需要另外将动态库的代码加载到内存中，如果不加载到内存中，则无法调用动态库中的函数。  
    加载动态库的方式有两种，  
    +  第一种：使用“动态库加载器”来加载，这种是最常见的方式  
    +  第二种：在程序中调用“加载函数”来加载  
    因为这两种加载方式的不同，所以在程序中调用“动态库函数”的方式也会有所不同。  

### 1）使用“动态库加载器”来加载动态库

#### （a）编写调用动态库函数的程序main.c  
使用“动态库加载器”加载时，调用动态库函数的方式与调用静态库函数是一样的。  

```c
#include <stdio.h>
#include "caculate.h"  //包含动态库态库的头文件

int main(void)
{
    double a = 10.5;
    double b = 20.6;
    double ret = 0;

    ret = add(a, b); //加
    printf("add: ret = %f\n", ret);

    ret = sub(a, b); //减
    printf("sub: ret = %f\n", ret);

    ret = mul(a, b); //乘
    printf("mul: ret = %f\n", ret);

    ret = div(a, b);  //除
    printf("div: ret = %f\n", ret);

    ret = power(a);  //求平方
    printf("power: ret = %f\n", ret);

    return 0;
}
```
此时相关文件目录如下：
```
libmake
├── add_sub.c
├── add_sub.o
├── caculate.h
├── libmycaculate.so
├── mul_div.c
├── mul_div.o
└── README.md
libuse
├── main
└── main.c

```

#### （b）链接动态库  
```shell
gcc main.c -o main -L../libmake -lmycaculate -I../libmake
```

`-L`：指定动态库所在的路径  
`-l`：指定动态库的名字，需要将lib和.so去掉    
通过以上两个选项，就能在指定路径下找到指定名字的动态库，然后链接这个动态库  
`-I`：指定动态库头文件的路径  

我们运行程序时会提示说`找不到动态库`，我们通过`ldd`命令可以查看程序`用到了那些动态库`，`ldd ./main`查看，也直接提示libmycaculate.so动态库无法被找到
```shell
root@9e2614e43d08:/workspace/libuse# ./main 
./main: error while loading shared libraries: libmycaculate.so: cannot open shared object file: No such file or directory
root@9e2614e43d08:/workspace/libuse# ldd ./main
        linux-vdso.so.1 =>  (0x00007ffcf430f000)
        libmycaculate.so => not found  //我们自己的动态库，还没加载到内存中所以找不到
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f2cad6ef000) //c标准库的动态库，printf等函数就是由它提供的
        /lib64/ld-linux-x86-64.so.2 (0x00007f2cadab8000) //这个是动态库加载器
```

+ 无法找到的原因？  
  因为“动态库加载器”去加载动态库时，找不到动态库，所以没有能加载到内存中    

+ 那么“动态库加载器”怎样才能找到动态库，并将动态库加载到内存中呢？  
  这个问题后面再解决  

+ 提问：为什么要链接动态库？  
    在程序main.c中我们明确的调用了add、sub等动态库函数，编译时必须对这些函数名进行符号解析，而符号解析所需要的信息被包含在了“.so动态库”中，所以编译时必须链接动态库，否则就会提示“函数没有定义的错误”，说白了就是符号解析失败。
   ```shell
    main.c:(.text+0x42): undefined reference to `add'
    main.c:(.text+0x82): undefined reference to `sub'
    main.c:(.text+0xc2): undefined reference to `mul'
    ....
   ```
   不过有意思的是，linux的下的“.so动态库”会直接包含符号解析所需的各种信息，但是windows下的.dll动态库则有所不同，这些符号解析的信息不在.dll中，而是在与.dll配套的“动态库引导文件”中，链接时只需要链接“动态库引导文件”即可进行符号解析。  
  总结起来就是：  
    + `在Linux下`  ：直接通过链接“.so动态库”来进行符号解析    
    + `在windows下`：通过链接“动态库引导文件”来进行符号解析，而不是直接链接“.dll动态库”   
  有关“动态库引导文件”，后面还会讲到，这里我们先建立点基本的映像  


+ 提问：编译链接后，main.c中add、sub等会变成什么?  
   add、sub等为动态库函数的函数名，函数名就是函数指针，所以编译后会变成函数的第一条指令的地址  
    
   如果函数定义就在自己的程序中，那么函数指针一定是绝对地址，因为自己程序中的函数代码会被加载内存中什么位置，在编译阶段就能确定，既然能够确定，那么编译时就直接将“函数指针”指定为绝对地址
   
   但是当调用的是动态库函数时，动态库中的函数定义并不在我们自己的程序中，而是在动态库中。  
   
   链接动态库时只会留下接口，不会将代码包含到自己的程序中，所以动态库函数的定义不在自己的程序中。  
   
   而且动态库被加载到内存中什么位置是不确定的，所以说动态库中每个函数在内存中的地址也是不确定的，那么编译时，应该将add、sub等函数名翻译为什么样的地址呢？  
   
   我们接下来解释一下这个问题。  
   
   不过我们的解释不是100%准确的，与实际情况有所差别，但是如果完全按照真实情况来讲的话，会很难理解，如果我们采用不太准确的方式来介绍，虽然有点不太准确，但是不会出大错，关键是好理解。  
   
   我们这么来理解，编译时add、sub等会被编译为相对地址，这个“相对地址”为函数在动态库中相对于“动态库起始位置”的偏移。  
   
   图：动态库函数相对地址   
   
   动态库在没有被加载到内存中之前，动态库在内存中位置是不确定，但是一旦加载到了内存中后，动态库在内存中的起始地址就是确定的，系统会记录下动态库在内存中的起始地址，当程序调用add、sub等动态库函数时，  “相对地址” + “动态库起始地址”  ————> add、sub等动态库函数在内存中的地址 , 通过这个地址即可跳转到动态库中add、sub函数处，开始执行这些函数的指令，执行完后再返回  
    
   图：
    
   实际情况会比我们这里描述的更难理解，而且涉及到地址映射的问题，我们这里不需要关心到这个层次  

#### （c）“动态库加载器”怎样才能找到动态库，并将动态库加载到内存中  

+  动态库加载器  
我们在第1章分析gcc -v的详细过程时就讲过，gcc编译链接程序时，会给我们的程序指定“动态库加载器”，
`/lib64/ld-linux-x86-64.so.2`   
前面通过ldd也查看到了这个玩意。  
动态库加载器是自动工作的，我们不需要关心如何去启动它。  

+  “动态库加载器”如何才能找到动态库呢？  
    “动态库加载器”是通过“动态库环境变量”来知晓，因为“动态库环境变量”中会包含各种动态库所在的路径，“动态库加载器”会自动到这些路径下去搜索。  
    比如C标准库的libc.so的路径就在“动态库环境变量”中，所以“动态库加载器”才会找到libc.so，否者printf、scanf这些函数就用不了，而且我们在第1章就介绍过，由于c标准库中的大部分函数会被频繁用到，所以gcc会默认自动链接libc.so。  
    `/home/zxf/Desktop/dynamic_lib`  
    总之，我们只要将我们的动态库路径/home/zxf/Desktop/dynamic_lib加入到“动态库环境变量”即可。  
    此时动态库加载器必然就能搜索到我们的动态库，然后将其加载到内存中。  

+ 疑问：如何设置Linux的“动态库环境变量”呢？  
    设置命令：  
    `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/zxf/Desktop/dynamic_lib`  
    设置完后，我们的程序就能正常运行了。  
    `export`：修改Linux环境变量的命令  
    `LD_LIBRARY_PATH`：“动态库环境变量”的名字，变量的内容就是各个动态库所在的路径  
    `$LD_LIBRARY_PATH`：$表示取变量的内容，所以$LD_LIBRARY_PATH代表的是“动态库环境变量”的内容  
    `:/home/zxf/Desktop`：在原有内容基础上，再加一个新的动态库路径，:为不同路径之间的间隔,新加的路径就是我们的动态库所在的路径。  
    有关环境变量请看《linux系统编程、网络编程》的第4章 进程环境这一章。  
    `疑问`：gcc时不是已经通过-L./dynamic_lib指定了动态库的路径了吗？  
    答：这只是给“编译链接”用的，与动态库加载无关。  

+  “动态库加载器”是如何加载动态库的  
    运行程序时，“动态库加载器”会首先检测程序中所用到的“动态库代码”，有没有被加载到内存中，  
    +   有：不用再加载了，因为动态库是共享的，内存中只需要一份即可   
    +   没有：到LD_LIBRARY_PATH指定的每一个路径下去寻找，找到“动态库”后就加载到内存中而且加载时，整个动态库代码会被全部加载到内存中。  

### 2）在程序中调用“动态库加载函数”来加载
+ （a）Linux下的动态库加载函数  
    这里特意强调了Linux下，意思就是Windows下的动态库加载函数与Linux是不一样的。  
     Linux下的动态库加载函数是c库函数，但是不是c标准库提供的，而是Linux这个平台的c库函数，也就是说在windows下不能使用Linux下的动态库加载函数。
    + dlopen：  
        - 函数原型：
                ```c
                #include <dlfcn.h>  
                void *dlopen(const char *filename, int flags);  
                ```

        - 功能：打开动态库文件，将动态库文件中的代码加载到内存中。  

        - 参数：
            `filename`：动态库的路径名，比如./dynamic_lib/libmycaculate.so，此时库的名字一定要写全名，lib和.so不能省略。  
            flags：打开方式  
                flags的选项有好多，由于dlopen函数用的并不多，所以这里只介绍我们会用到的RTLD_NOW选项。  
                RTLD_NOW：简单理解就是，立即打开动态库文件并加载到内存中，当然这个理解并不准确，但是我们目前就先这么理解。如果以后大家真用到了这个函数时，在自己去深入了解这个函数。  

        - 返回值：
            成功：返回一个void *指针，后续利用这个指针就可以去调用“动态库函数”。  
            失败：返回NULL。  


    + dlclose：  
            dlopen用于加载动态库，dlclose刚好相反，用于将动态库从内存中卸载掉。  
            `int dlclose(void *handle);`
            参数为dlopen的返回值。  
            返回值：成功返回0，失败返回非零值  
            不过当多个程序都在共享使用动态库时，只要还有一个程序还在调用动态库，dlcose时就不会立即卸载，只有当最后一个调用动态库的程序dlcolse时，才会真正的从内存中卸载掉动态库。  

    + dlsym  
        - 函数原型       
            ```c
            #include <dlfcn.h>
            void *dlsym(void *handle, const char *symbol);
            ```

        - 功能    
                动态库被dlopen加载到了内存中后，每个库函数的内存地址就是确定的，此时只要得到了add、sub、mul等函数入口地址（函数指针：绝对地址），自然就能调用这些函数了。  
                dlsym的作用就是用来返回“每个动态库函数”在内存中函数指针，只不过返回的类型为void *，使用时需要强制转为对应的函数指针类型。  
                图：  

        - 参数  
            `handle`：dlopen返回的指针  
            `symbol`：库函数的名字，为一个字符串，dlsym会通过名字去查找动态库函数的函数指针。  


        - 返回值    
            成功：返回某动态库函数在内存中的函数指针  
            失败：返回NULL  


        - 使用例子  
            ```c
             double (*funp)();
             funp=(double (*)())dlsym(handle,"sub"); 
            ```
            由于“动态库代码”中保留了符号名称（字符串），所以才能在动态库代码中通过函数名称找到该函数的函数指针。

+ （b）main.c  
    ```c
    #include "caculate.h"  //包含静态库的头文件
    #include <stdio.h>
    #include <dlfcn.h>

    int main(void)
    {
            double a = 10.5;
            double b = 20.6;
            double ret = 0;

            double (*funp)() = NULL; //函数指针变量，用于存放dlsym返回的库函数的函数指针
            void *handle = NULL;  //存放dlopen所返回的指针

            //打开动态库文件，并将代码加载到内存中，为了让代码简洁一些，我们省略出错处理
            handle = dlopen("./dynamic_lib/libmycaculate.so", RTLD_NOW); 


            //返回add库函数在内存中的绝对地址，并强制转换为double (*funp)()
            funp=(double (*)())dlsym(handle,"add");  
            ret = funp(a, b);  //通过add的函数指针来调用动态库中add函数
            printf("add: ret = %f\n", ret);

            funp=(double (*)())dlsym(handle,"sub");  //同上
            ret = funp(a, b);  //同上
            printf("sub: ret = %f\n", ret);

            funp=(double (*)())dlsym(handle,"mul"); 
            ret = funp(a, b);
            printf("mul: ret = %f\n", ret);

            funp=(double (*)())dlsym(handle, "div");
            ret = funp(a, b);
            printf("div: ret = %f\n", ret);

            funp=(double (*)())dlsym(handle,"power");
            ret = funp(a);
            printf("power: ret = %f\n", ret);

            dlclose(handle); //从内存中卸载掉动态库

            return 0;
    }
    ```

+  （c）编译main.c    
    `gcc main.c -o main -ldl`  
    运行程序时，会调用dlopen函数会将libmycaculate.so动态库打开并加载到内存中，然后dlsym函数会返回每个动态库函数在内存中的函数指针，然后通过函数指针即可调用这些库函数。    
    +  -ldl是什么意思?  
        在linux下，dlopen、dlsym、dlclose由相应的c库提供，只不过并不是c标准库。而且这个c库还是动态库，名字叫libdl.so，编译时我们需要通过-ldl来链接。  
        如果不链接libdl.so的话，就没办法对dlopen、dlsym等进行符号解析。  
        提供dlopen、dlsym、dlclose函数的c库是Linxu平台的c库，只在linux平台有效。  

        `疑问`：为什么没有通过-L指定动态库libdl.so的路径？  
        答：libdl.so动态库的路径加入了环境变量，可以自动找到。
            不过要注意的是，这个环境变量不是前面说的那个，与动态库加载有关的“动态库环境变量”，而是另外的环境变量，有关这个环境变量我们就不再介绍了，《Linux系统编程、网络编程》会讲。  
            `libm.so  libptread.so  -lmycaculate`  
        我们在使用数学库、线程库时，要求指定-lm和-lpthread，比如：  
        ```shell
        gcc **.c **.c -o a.out -lm   //libm.so
        gcc **.c **.c -o a.out -lpthread  //libpthread.so
        ```

    +  为什么没有链接libmycaculate.so?  
        因为程序中没有直接调用add、sub等动态库函数，"add"、"sub"等只是dlsym的参数而已，不涉及到对add、sub等函数名的符号解析，所以不需要链接libmycaculate.so。 
