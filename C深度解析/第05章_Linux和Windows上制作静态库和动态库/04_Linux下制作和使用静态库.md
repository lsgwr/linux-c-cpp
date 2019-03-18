
# 8.2.1 制作、使用静态库

## （1）编写需要制作为静态库的代码

代码实现add/sub/mul/div/power等算数运算函数，然后做成静态库，在我们的程序中链接了这个静态库之后，我们就可以调用这些函数来进行算数运算了  
		
代码文件：  
+ `caculate.h`：头文件，存放库函数的声明  
+ `add_sub.c`：加法、减法  
+ `mul_div.c`：乘法、除法、平方  

### 1）caculate.h

```c
#ifndef H_CACULATE_H
#define H_CACULATE_H

extern double add(double arg1, double arg2);
extern double sub(double arg1, double arg2);
extern double mul(double arg1, double arg2);
extern double div(double arg1, double arg2);
extern double power(double arg);

#endif
```

在程序中使用这些函数时，我们需要对这些函数进行声明，为了方便我们进行声明的操作，我们需要把这些函数声明放到.h中，到时候只要包含这个.h即可。  

我们的例子比较简单，目的只是为了向大家演示如何制作和使用静态库，实际上在.h不仅仅只会放函数声明，还需要各种宏定义、结构体类型定义、inline函数等等。  

库函数的.h与我们自己的.h没有任何区别，只不过.h所对应的.c被做成了静态库而已。  

### 2）add_sub.c

```c
#include "caculate.h"

double add(double arg1, double arg2)
{
	double sum = 0;

	sum = arg1 + arg2;

	return sum;
}

double sub(double arg1, double arg2)
{
	double sum = 0;

	sum = arg1 - arg2;

	return sum;
}
```

### 3）mul_div.c

```c
#include "caculate.h"

double power(double arg)
{
	double sum = 0;

	sum = mul(arg, arg);

	return sum;
}

double mul(double arg1, double arg2)
{
	double sum = 0;

	sum = arg1 * arg2;

	return sum;
}

double div(double arg1, double arg2)
{
	double sum = 0;

	sum = arg1 / arg2;

	return sum;
}
```

注意：库里面是不能包含main函数的，main在我们自己的程序中。
							
## （2）将源码制作为静态库文件            

### 1）得到.o文件 

```c
gcc -c add_sub.c -o add_sub.o 
gcc -c mul_div.c -o mul_div.o 
```
### 2）将.o文件打包为静态库文件

```shell
ar  -crv  ./libcaculate.a  add_sub.o  mul_div.o
```

+ （a）`ar`：打包命令  
+ （b）`-crv`：显示打包过程  
+ （c）`./libcaculate.a`：静态库的路径名  
     + `./`：静态库的存放路径，你可以指定为任何路径，目前为了演示的便利，我们就放在./下  
     + `libcaculate.a`：静态库的完整名字，前缀lib和后缀.a为固定格式，中间的caculate才是真正的静态库的名字。制作.a静态库时前缀lib为固定格式  
+ （d）`add_sub.o`  `mul_div.o`  
	要打包为静态库文件的.o（原料）  

如果制作成功，使用ls查看时，你会发现在当前目录下就有一个libcaculate.a文件。file命令查看时，会告诉你静态库文件其实是一个归档文件。  
```shell
root@9e2614e43d08:/workspace/libmake# file libcaculate.a 
libcaculate.a: current ar archive
```

再说说ar命令：  
ar命令其实“归档命令”(archive的前两个字母)，专门用来实现对文件进行归档，所以说制作静态库文件其实就是制作一个归档文件  
归档文件和压缩文件很相似，只不过归档文件只打包不压缩，但是压缩文件不仅会打包，而且还会进行压缩  

静态库文件放在了ubuntu桌面下的static_lib目录下。  
				
## （3）使用静态库文件

### 1）写一个调用库函数的main.c	
```c
#include <stdio.h>		
#include "caculate.h"  //包含静态库的头文件

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

当前的目录结构如下：
```
libmake
├── add_sub.c
├── add_sub.o
├── caculate.h
├── libcaculate.a
├── mul_div.c
├── mul_div.o
└── README.md
libuse
├── main
└── main.c

```

包含静态库的头文件时，如果caculate.h不在当前路径时怎么办，    
+ 可以在""中指定.h所在的路径  
+ gcc时通过-I选项，将.h所在路径加入"头文件系统路径"  

有关“头文件”的相关内容，我们在第2章有非常详细的介绍，不清楚的同学，请看这一章。  

### 2）编译main.c并链接静态库


+ （a）如果不链接静态库会怎样
    ```shell
    /tmp/ccTCMbDN.o: In function `main':
    main.c:(.text+0x42): undefined reference to `add'
    main.c:(.text+0x82): undefined reference to `sub'
    main.c:(.text+0xc2): undefined reference to `mul'
    main.c:(.text+0x139): undefined reference to `power'
    collect2: error: ld returned 1 exit status
    ```

报一堆的链接错误，提示链接时找不到这些函数的定义，这种链接错误是我么经常会碰到的错误。   

当你在调用某个函数时如果把函数名写错了，同样也会提示你找不到函数的定义的错误，因为而错误的函数名肯定没有对应任何的函数定义，自然会报错。  

在我们这里并没有把名字写错，而是没有链接定义这些函数静态库，所以找不到函数的定义。  


+ （b）链接静态库	

    ```shell
    gcc main.c -o main -L../libmake -lcaculate -I../libmake
    ```

   + -I：指定caculat.h所在的路径，路径为`../libmake`

   + -L：指定静态库所在的路径（路径为`../libmake`），链接时会到该路径下去查寻找静态库。  
       + `疑问` ：能不能省略静态库的路径？  
         答：可以  
            只要将所在路径加入了环境变量，链接时会指定到该路径下寻找静态库，此时我们不用自己指定静态库所在的路径。   
            当然还有一种办法，那就是你可以将“库文件”放到之前早就被加入了环境变量的路径，这样也是可以的。    
	    
        + `疑问`：如何将路径加入环境变量呢？  
          答：我们在《Linux系统编、程网络编程》课程的第4章——进程环境中有详细介绍，请大家看这部分课程内容。在课程中windows和Linux的环境变量我们都有介绍了。  

    + -l：注意是小写L，这个用于指定库的名字  
        +  `指定库名字时需要将前缀lib和后缀.a省略`  
        +  `-L指定所在路径，-l指定库名字`，如此就会在指定的路径下面找到指定名字的静态库库文件，然后链接它  
           其实有关-l，我们在第1章介绍gcc -v详细信息就提到过，有关这一点，请大家看第1章的内容。 
