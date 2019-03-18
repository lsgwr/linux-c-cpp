# 8.3.1 制作、使用静态库

## （1）创建制作静态库的c工程
+ 1）打开Codeblocks  
+ 2）File——>New——>Project———>Static library——>Next——>输入工程文件名（比如caculate） 和 选择工程存放路径   
+ 3）新建三个文件，分别命名为add_sub.c、mul_div.c、caculate.h文件的内容不变，还是之前的那些内容  
+ 4）编译制做静态库
    编译静态库c工程，最后就得到了静态库libcaculate.a，它被放在了工程目录下的`bin/Debug/`或者`bin/Release/`下   
    一般来说在windows平台下，静态库的名字应该叫***.lib，但是前面也说过，静态库的名字与编译器也有关系，比如使用gcc编译器来制作静态库时，不管针对的是什么平台，名字都是.a结尾的，当然还有一个lib前缀   
+ 5）我们可以将静态库libcaculate.a和caculate.h集中放到某个目录下，以方便后续使用.比如在桌面创建一个static_lib目录，将libcaculate.a和caculate.h放在里面  
		
## （2）使用静态库
+ 1）关闭制作静态库的工程，创建一个使用静态库的c工程  
+ 2）新建一个main.c，然后将之前调用静态库的main.c中的内容，复制到当前工程的main.c中  
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

+ 3）设置静态库的链接
   + （a）指定caculate.h的路径  
            Settings——>Compiler——>Global compiler settings——>Serch directories——>add——>caculate.h所在路径  
            当然，我们也可以直接将caculate.h复制到main.c所在的目录，此时直接#include "caculate.h"即可  

   + （b）指定要链接的静态库  
            Settings——>Compiler——>Global compiler settings——>Linker settings——>add——>选择你要链接的静态库  

+ 4）编译链接、并运行程序  
        编辑链接时就会链接我们指定的静态库，然后程序即可正常运行  
