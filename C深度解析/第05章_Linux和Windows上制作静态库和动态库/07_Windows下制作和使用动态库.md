# 8.3.2 通过IDE方式来制作、使用动态库

## （1）创建制作动态库的c工程
+ 1）打开Codeblocks
+ 2）File——>New——>Project———>Dynamic Link library——>Next——>输入工程文件名比如mycaculate 和 选择工程存放路径
+ 3）新建三个文件，分别命名为add_sub.c、mul_div.c、caculate.h文件的内容不变。
+ 4）编译得到动态库
    编译后就得了动态库，也被放在了工程目录下的bin/Debug/或者bin/Release/下。
        dynamic.dll  
        libdynamic.a   

    在Linux下制作动态库时，所得到只有一个***.so文件，但是制作windows动态库时，所得到文件会有两个：  
    + `***.dll`：真正的动态库  
    + `***.a`：windows下动态库的“动态库引导文件”  

    这个两个文件合起来等价于***.so，***.a这个“动态库引导文件”也是一个静态库，只不过这个静态库里面放的只是动态库符号解析所用基本信息，而不是库函数。  
    + （a）链接Linux下的动态库时：链接的是***.so  
    + （b）链接windows下的动态库时：链接的是“动态库引导文件”，而不是.dll  
+ 5）将dynamic.dll、libdynamic.a和caculate.h集中放到某个目录下，以后续方便使用.比如在桌面创建一个dynamic_lib目录，然后放在里面  
							
## （2）使用动态库
根据加载动态库方式的不同，分为两种情况：  

+  通过“动态库加载器”加载  
+  在程序中调用“动态库加载函数”来加载  

### 1）方式1：通过“动态库加载器”加载  
+ （a）创建一个使用动态库的工程  
        File——>New——>Project———>Console application ——>...  

+ （b）将之前调用动态库的main.c中的内容，复制到新工程的main.c中
    main.c:
    ```c
    #include "caculate.h"  //包含静态库的头文件
    #include <stdio.h>

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
            ret = div(a, b);
            printf("div: ret = %f\n", ret);

            ret = power(a);  //除
            printf("power: ret = %f\n", ret);

            return 0;
    }
    ```

+ （c）设置对动态库的链接
    +  指定caculate.h的路径，include时才能找到  
        Settings——>Compiler——>Global compiler settings——>Serch directories——>add——>caculate.h所在路径  
        同样的，我们也可以直接将caculate.h复制到工程目录下，include "caculate.h"时，直接在当前目录下就可以找到狗文件  
    +  指定要链接的“动态库引导文件”    
        Settings——>Compiler——>Global compiler settings——>Linker settings——>add——>“动态库引导文件”所在的路径  
    +  将`***.dll`复制到`***.exe`可执行程序所在目录  
            运行程序时，动态库加载器才能找到这个动态库，并加载到内存中  

+ （d）编译链接、并运行  
    编辑链接时，会链接“动态库引导文件”，对程序中的add、sub等进行符号解析. 要不然会提示找不到add、sub等函数的函数定义  
    编译之后就得到了***.exe可执行程序，运行程序时，“动态库加载器”会将***.exe所在目录下的 mycaculate.dll动态库加载到了内存中，当然，如果之前已经加载了就不再加载   
    `疑问`：为什么linux的动态库和windows动态库会存在区别，.so没有动态库引导文件，而.dll确有动态库引导文件？  
    `答`：这个区别是由linux和windows目标文件的格式不同导致的，Linux目标文件格式ELF格式，windows下的目标文件格式为PE格式，因为这两种格式的不同，而导致了动态库的区别。  

### 2）方式2：在程序中调用“动态库加载函数”来加载
linux平台所提供动态库加载函数为dlopen、dlsym、dlclose，同样的，windows平台这边也有对应的“动态库加载函数”，分别是LoadLibrary、GetProcAddress、FreeLibrary  
    `LoadLibrary`：类比于`dlopen`  
    `GetProcAddress`：类比于`dlsym`  
    `FreeLibrary`：类比于`dlclose`  
    使用这几个函数时需要包含windows.h，类比于Linux这边的dlfcn.h  
    LoadLibrary、GetProcAddress、FreeLibrary与dlopen、dlsym、dlclose还是有些不同之处：  
    dlopen、dlsym、dlclose  
        Linux平台的C库函数，由libdl.so动态库提供，需要通过-ldl链接对应的动态库。    
        这几个函数只在Linux平台有效。  
    LoadLibrary、GetProcAddress、FreeLibrary  
        这几个函数是Windows的OS API，不需要指定什么`-l***`来链接。  
        那么这几个函数也只能在windows下使用  

+ （a）创建一个调用LoadLibrary等函数来加载动态库的工程  
    File——>New——>Project———>Console application ——>...  

+ （b）在main.c中编写使用LoadLibrary等来加载并使用动态库的代码  
    main.c：  
    ```c
    #include <windows.h>
    #include "caculate.h"
    #include <stdio.h>
    int main(void)
    {	
            double ret = 0;
            HINSTANCE handle;  //类比于Linux这边void *handle
            double (*funp)() = NULL;  //函数指针变量

            //类比于dlopen
            handle = LoadLibrary("C:\\Users\\Administrator\\Desktop\\dynamic_lib\\mycaculate.dll"); //windows编译器所用的动态库为.dll结尾

            funp = (double (*)())GetProcAddress(handle, "add");  //类比于dlsym
            ret = funp(2.3, 3.6);
            printf("%f\n", ret);		

            funp = (double (*)())GetProcAddress(handle, "sub");
            ret = funp(2.3, 3.6);
            printf("%f\n", ret);		

            funp = (double (*)())GetProcAddress(handle, "mul");
            ret = funp(2.3, 3.6);
            printf("%f\n", ret);	

            funp = (double (*)())GetProcAddress(handle, "div");
            ret = funp(2.3, 3.6);
            printf("%f\n", ret);		

            funp = (double (*)())GetProcAddress(handle, "power");
            ret = funp(2.3);
            printf("%f\n", ret);	


            FreeLibrary(handle); //类比于dlclose(handle)

            return 0;
    }
    ```

+ （c）指定caculate.h的路径,与以前是一样的  

+ （d）编译运行   

    程序运行起来后：  
    +  LoadLibrary先将指定路径下的动态库打开，并加载到内存中.当然，如果内存中已经有一份了，LoadLibrary则不会重复加载的  
    +  通过GetProcAddress函数，即可获得某个动态库函数在内存中的函数指针  
    +  得到动态库函数的函数指针后，就可以调用这个动态库函数了  
