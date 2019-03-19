# 7. main函数的参数argc、argv 与 返回值	

  我们常见的main函数为int main(void)，但实际上main函数可以有形参，因为main函数也是被启动代码所调用的函数，main函数也会被别人调用，所面也是可以被传参，参数形式为
```c
int main(int argc, char **argv)
```
直接讲这两个参数，估计不太好理解，我们先从"字符串指针数组"说起。
	
	
## 7.1 字符串指针数组 

### 7.1.1 什么是"字符串指针数组"

```c
char *buf[] = {"how", "are", "you"};  //字符串指针数组
```
作为字符串常量放在了.rodata中，buf[]中的每个元素只是用来存放每个字符串的字符串指针。图：

"how", "are", "you"为字符串常量，各自代表的是第0个元素空间的指针（字符串指针），字符串的每个字节空间的类型为char，那么空间指针的指针类型则为char *，自然第0个字符所在空间的指针也为`char *`，所以存放字符串指针的数组也为`char *`  

```c
char *buf[] = {"how", "are", "you"}; // 可以等价的理解为就是定义三个指针变量，用于存放字符串指针
```

```c
// 既然数组每个元素（变量）的类型为char *，那么数组每个元素指针的类型就为char **
char *buf[0] = "how"; 
char *buf[1] = "are";
char *buf[2] = "you";
```
		
### 7.1.2 传递"字符串指针数组"
	
```c
void fun(int m, char **p) 
{
  int i = 0;

  for(i=0; i<m; i++)
  {
    printf("%s\n", p[i]);
  }
}

int main(void)
{
  char *buf[] = {"how", "are", "you"};

  fun(3, buf);//buf等价于&buf[0], buf[0]的类型为char *，&buf[0]的类型就为char **

  return 0;
}
```

形参的等价写法：
```c
void fun(int m, char **p)  //*p等价于p[]
{
}
```

等价于
```c
void fun(int m, char *p[])  
{
}

```
字符串指针数组，一般末尾都会使用NULL结尾，这样的话实际上可以通过NULL来判断结尾，比如下面这个例子。

```c
void fun(char *p[])
{
  int i = 0;

  for(i=0; p[i]!=NULL; i++)
    printf("%s\n", p[i]);
}

int main(void)
{
  char *buf[] = {"how", "are", "you", NULL};

  fun(buf);

  return 0;
}
```
	

## 7.2 `int main(int argc, char *argv[])` 
	
根据`argv[]`与`*argv`的等价关系，`char *argv[]`等价于`char **argv`

```c
int main(int argc, char **argv)
{
  return 0;
}
```

启动代码调在用main函数时，可以给main传递一个“字符串指针数组”  

```c
char *buf[] = {"xxx", "xxx", "xxx", ..., NULL};
int n = sizeof(buf)/sizeof(char *)-1;
main(n, buf);  //buf等价&buf[0]，buf[0]的类型为char *，&buf[0]的类型char **
```
+ （1）argc：argc为argment count的缩写，放的是字符串的个数。
+ （2）argv：argv为argment vector的缩写，放的是“字符串指针数组”第0个元素指针
     argment vector被称为“参数矢量”，矢量就是带有指向的东西，由于指针带有指向作用，因此在c中，指针也被称为矢量。

`疑问`：main函数的形参是不是一定要命名为argc和argv呢？  
答：当然不是，取什么名字都可以。
    ```c
    int main(int a, char **b)
    {
      return 0;
    }
    ```
    不过我们还是按照大家都熟悉的，约定俗成的名字来会更好些。
			
		
## 7.2 main函数参数的作用

### 7.2.1 裸机时（没有OS）
	裸机时main函数的传参没有什么意义，所以裸机运行c程序时，main函数的形式基本都为`int main(void)`或者`void main(void)`
	
### 7.2.2 有OS时

#### （1）作用
当然，我这里说的OS指的是Linux、Windows等复杂的操作系统，而不是单片机上运行的RTOS这种小型的实时OS main函数的参数用于实现父进程和子进程之间的参数传递：  
```c
              字符串指针数组
  父进程 ——————————————————————> 子进程（c程序：启动代码———————————————>main的argc和argv）
```
有关父子进程的更多情况，请看《c深度解析》的第1章中的“程序加载、运行”课程。


#### （2）父子进程传参举例：在命令行运行程序时，输入命令行参数，传递命令行参数

```c
#include <stdio.h>

int main(int argc, char **argv)
{
  int i = 0;

  for(i=0; i<argc; i++)
  {
    printf("%s\n", argv[i]);
  }	

  return 0;
}
```

在命令行运行程序，然后在命令行输入命令行参数，然后main函数会打印出命令行参数。
```shell
>a.exe afasff fds f dasf as 

运行结果：
a.exe 
afasff 
fds 
f 
dasf 
as 
```


字符串传递的过程为：

+ 1）父进程（命令行程序）
  + （a）得到键盘输入的字符串，并构建出"字符串指针数组"
     ```c
      char *buf[] = {".\qq.exe", "afasff", "fds", "f", "dasf", "as", NULL}; 
      int n = sizeof(argv)/sizeof(char *)-1; 
     ```

  + （b）父进程创建“子进程”，在子进程中“加载运行”q.exe这个c程序

  + （c）将buf和n传递给“子进程”中所运行q.exe程序的启动代码

+ 2）启动代码再将n和buf传递给main函数的形参argc和argv  
    main函数就可以通过arg、argv访问"字符串指针数组"，通过指针数组中的每个"字符串指针"去访问每个字符串  
    ```c
                           n  buf                                n   buf
      父进程（命令行程序）————————————> 子进程（qq.exe：启动代码 ————————————> main的argc和argv）
    ```

    `疑问`：在命令行执行程序时，传递命令行参数有什么意义呢？  
    答：当然有意义，但是我们这里不解释，大家可以看《linux系统编程、网络编程》这个课程，学了这个课程后，你自然知道命令行参数有什么意义  

    由于字符串指针数组以NULL结尾，所可以通过NULL判断结尾
    ```c
    for(i=0; i<argc; i++)
    ```

    可以改为：

    ```c
    for(i=0; argv[i]!=NULL; i++)
    ```

			
			
## 7.2 main函数的返回值
函数使用return的目的，是想将返回值返回给调用者，main函数的调用者是启动代码，所以main函数return的返回值，肯定是返回给调用main函数的启动代码的，但是启动代码拿到返回值后，又会交给谁呢？   

### 7.2.1 裸机时（没有OS）

返回值返回给到“启动代码”就终止了，启动代码拿到返回值后也没有什么意义，也就说裸机时，main函数返回值并没有什么意义   
所以说以前好多的裸机c程序，main函数都喜欢将返回值的类型写为void，比如：  
```c
void main(void)
{

}
```
	
### 7.2.2 有OS时	
启动代码会将返回值交给OS内核，这个肯定是由意义，操作系统内核拿到返回值能后，有什么作用呢？  
这个问题请大家看《linux系统编程、网络编程》  
