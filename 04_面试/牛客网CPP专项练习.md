# 牛客网CPP专项练习

### 1.c++中，声明const int i,是在哪个阶段做到 i只可读的？（A）
+ A.编译
+ B.链接
+ C.运行
+ D.以上都不对

解析：const用来说明所定义的变量是只读的。 这些在编译期间完成，编译器可能使用常数直接替换掉对此变量的引用。

### 2.对于条件表达式(k)?(i++):(i--)来说，其中的表达式k等价于（C）
+ A.`k==0`
+ B.`k==1`
+ C.`k!=0`
+ D.`k!=1`

【解释】对于该条件表达式应理解为；k为真时返回i++，否则返回i--，在C语言中表达式的值非0表示真，为0表示假，所以k为真应表示为k!=0.故正确答案为C

### 3.以下关于指针的说法,正确的是(C)

+ `int *const p`与`int const *p`等价
+ `const int *p`与`int *const p`等价
+ `const int *p`与`int const *p`等价
+ `int *p[10]`与`int (*p)[10]`等价

> 解读如下：

+ `int *const p`与`int const *p`等价    前者是指向整数数据的常量指针，指针不可再被修改，后者是指向数据类型为常量的指针p，p所指向的数据值不可更改
+ `const int *p`与`int *const p`等价    const int 同int const
+ `const int *p`与`int const *p`等价
+ `int *p[10]`与`int (*p)[10]`等价    前者是一个数组，数组里存放十个这样的指向整形数据的指针，后者是一个数组指针，p指向存放整形数据的数组

那如何区分这几类呢? 带两个const的肯定是指向常量的常指针，很容易理解，主要是如何区分常量指针和指针常量:

一种方式是看 * 和 const 的排列顺序，比如

+ int const* p; //const * 即常量指针
+ const int* p; //const * 即常量指针
+ int* const p; //* const 即指针常量

还一种方式是看const离谁近，即从右往左看，比如

+ int const* p; //const修饰的是*p，即*p的内容不可通过p改变，但p不是const，p可以修改，*p不可修改；
+ const int* p; //同上
+ int* const p; //const修饰的是p，p是指针，p指向的地址不能修改，p不能修改，但*p可以修改；

### 4.如果x=254，函数返回值为：(B)
```cpp
int func(int x) {
    int countx = 0;
    while (x) {
        countx++;
        x = x & (x - 1);
    }
    return countx;
}
```
+ 6
+ 7
+ 8
+ 0

> 解析如下：

```cpp
x = x&(x-1);//求x的二进制表达式有多少个1
x = x|(x-1);//求x的二进制表达式有多少个0
```

从右向左数，找到第一个1，把1后面的所有的数字都变为0。如x=1000110，x&(x-1)=1000100就是把x右边的第一个1后面的数变为0（包括1）。

如果10000的话，结果就是00000了！这样就可以利用这个特性来计算这个十进制书转化为二进制数有多少个1！

### 5.以下正确的函数原型声明语句是(C)
+ A.`double fun(int x,int y)`
+ B.`double fun(int x;int y)`
+ C.`double fun(int,int);`
+ D.`double fun(int x,y);`

```txt
/C++中的函数原型是指函数声明的形式：
返回值类型 函数名(参数列表);。注意分号是函数原型的组成部分，去掉分号的部分可以称为函数头，是函数定义的起始部分。
这里的参数列表和定义中的列表语法形式相同，其中的参数是形式参数，只需要指定类型，名称可有可无。形式是以下任意一种：
1.空——C中表示接受任意参数，C++中表示接受0个参数；
2.“void”——C中接受0个参数，C++中可省略；
3.“类型名 参数名,”，或者以上形式的重复，但末尾不能有逗号；参数名会被编译器无视，不必和定义一致；
4.“...”——用于C++，表示接受任意参数。
函数原型作为声明，作用是提示编译器，作为标识符的函数名，在声明之后或外部编译单元/库文件存在定义，以抑制编译器遇到这个标识符时产生标识符未定义的编译错误。原型作为语法技术的提出，出发点就在于这个作用，利用它可以方便地定义互相递归的函数，以及引用外部库文件的符号。
```

### 6.在64位操作系统上，下面程序返回什么结果：(D)
```cpp
int main() {
    int * k[10][30];
    printf("" % d\ n "", sizeof(k));
    return 0;
}
```

+ 4
+ 8
+ 1200
+ 2400

> 解析如下

```txt
int *k[10][30]; //声明了int型的指针数组 即数组里放的是int型的指针，8*10*30=2400  
int (*k)[10][30]; // 这样声明的结果就是 8，这个是声明了 数组指针
```

### 7.以下能对二维数组a进行正确初始化的语句是（B）
+ `int a[2][ ]=({1,0,1},{5,2,3});`
+ `int a[ ][3]={{1,2,3},{4,5,6}};`
+ `int a[2][4]=({1,2,3},{4,5},{6});`
+ `int a[ ][3]={(1,0,1)(),(1,1)};`

> 解析：二维数组的第二维一定要指定

+ A选项：最后一个维度没有指明，小括号套花括号；
+ B相当于int a[][3]={3,6}；其余元素为0；    正确
+ C维度超过2
+ D空括号编译过不了


### 8.请问运行Test 函数会有什么样的结果？（`A`）
```cpp
void GetMemory(char ** p, int num) {
    * p = (char * ) malloc(num);
}
void Test(void) {
    char * str = NULL;
    GetMemory( & str, 100);
    strcpy(str, "hello");
    printf(str);
}
```

+ hello
+ 空
+ 出错

> 解析：

先把题目改成如下:
1.把函数参数从二级指针改成一级指针之后的代码
```cpp
voidGetMemory(char*p,intnum)
{
   p = (char*)malloc(num);
}
voidTest(void)
{
   char*str = NULL;
   GetMemory(str,100);
   strcpy(str,"hello");
   printf(str);
}
```
结果就是str为空，也就是函数的操作并没有影响str。

很明显，指针就是传个地址给函数参数，那么p也是指向空。而操纵的是p而对str没有影响。

2.而源代码是二级指针

```cpp
*p = (char*)malloc(num);
```
*p就是str的地址，操作的也就是str，即给*p分配内存。

总结如下:
**对于函数传字符串或者通过malloc分配内存，都需要使用二级指针**

### 9.以下代码是哪一句可能导致的编译错误?(D)
```cpp
#include <iostream>
using namespace std;
class Test
{
public:
	Test() { cout << "i like zk"; }
	Test(int) { cout << "i like wangyi"; }
	void exe() { cout << "this is my choice"; }
};
int main()
{
	Test a(1);//1
	a.exe();  //2
	Test b(); //3
	b.exe();  //4
	Test c;   //5
	c.exe();  //6
    return 0;
}
```

+ 1
+ 2
+ 3
+ 4
+ 5
+ 6

> 3出的问题(声明成函数了)，但是到4才会体现出来

### 10.请声明一个指针，其所指向的内存地址不能改变，但内存中的值可以被改变。(B)
+ `const int const *x = &y;`
+ `int * const x = &y;`
+ `const int *x = &y;`
+ `int const *x = &y;`
+ `const int * const x = &y;`

> 解析：

+ A，指针所指向的内存不可变，内存中的值也不能通过指针改变，错误；
+ B，指针所指向的内存不可变，内存中的值可以改变，正确；
+ C，指针所指向的内存可变，但内存中的值不能通过指针改变，错误；
+ D，指针所指向的内存可变，但内存中的值不能通过指针改变，错误；
+ E，指针所指向的内存不可变，内存中的值也不能通过指针改变，错误；

### 11.以下程序运行后的输出结果是（B）？
```c
#include <stdio.h>

int main() {
    int p[7] = {11, 13, 14, 15, 16, 17, 18};
    int i = 0, j = 0;
    while (i < 7 && p[i] % 2 == 1) {
        j += p[i++];
    }
    printf("%d\n", j);
}
```

+ 23
+ 24
+ 25
+ 26

> 解析：注意while一旦不满足条件是直接退出地哦

### 11.请问下面的程序最后会产生多少个进程：（D）
```c
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int i;
    for (i = 0; i < 5; i++) {
        int pid = fork();
        if (pid == 0) {
            //do something 
        } else {
            //do something 
        }
    }
    // do somthing,sleep
    return 0;
}
```

+ 5
+ 10
+ 15
+ 32

> 解析：

```txt
i=0时，共有两个进程: 主进程和主进程创建的第一个进程
i=1时，以上两个进程分别创建新的进程，此时共有四个进程
i=2时，以上四个进程分别创建新的进程，此时共有8个进程
....
依次类推, 当i=n时，共创建2^(n+1)个进程
```

### 12.已知: int m=10；下列表示引用的方法中，正确的是:(C)
+ `int&Z;`
+ `int &t=10;`
+ `int&X=m;`
+ `float&f=&m;`

> 解析：

```txt
A、引用必须被初始化
B、引用类型的初始值必须是一个对象
C、正确
D、错误，1、非常量引用的初始值必须是左值 2、不能用int类型的值初始化double类型的引用
```

### 13.以下关于C++的描述中哪一个是正确的：(`C`)
+ 任何指针都必须指向一个实例
+ 子类指针不可以指向父类实例
+ 任何引用都必须指向一个实例
+ 引用所指向的实例不可能无效

### 14.有以下一段代码,编译时会产生错误的语句有：(C)
```cpp
#include <iostream>

using namespace std;

class A {
public :
    void run(void) {
        cout << "run()" << endl;
    }

    void run(int a) {
        cout << "run(A)" << endl;
    }
};

class B : public A {
public :
    void run(int a) {
        cout << "run(B)" << endl;
    }

};

int main(void) {
    B b;
    b.run(0); //语句1
    b.A::run(1); //语句2
    b.run(); //语句3
    b.A::run(); //语句4
    return 0;
}
```

+ 语句1
+ 语句2
+ 语句3
+ 语句4

> 解析：派生类和基类函数同名了，基类函数会被隐藏。

### 15.有以下类定义，若有语句定义rectangle r; r.setLength(3,5); 则编译时无语法错误的语句是（AB）
```cpp
#include <iostream>

using namespace std;

class shape {
public:
    virtual int area() = 0;
};

class rectangle : public shape {
public:
    int a, b;

    void setLength(int x, int y) {
        a = x;
        b = y;
    }

    int area() { return a * b; }
};
```

+ `shape *s1=&r;`
+ `shape &s2=r;`
+ `shape s3=r;`
+ `shape s4[3];`

> 解析：有纯虚函数的不允许实例化。C，D都是要创建shape的对象，所以不可以

### 16.在c++中，输出是多少?(`A`)
```cpp
const int i = 0; 
int *j = (int *) &i; 
*j = 1; 
printf("%d,%d", i, *j)
```

+ 0，1
+ 1，1
+ 1，0
+ 0，0

> 这个题一定要注意是在C++中的运行结果。

```txt
结果输出为0,1
分析：

C语言中的const是运行时const，编译时只是定义，在运行才会初始化。C语言中const变量不能用于成为数组长度等作为编译时常量的情况，原因就在此。C语言const变量在运行时改变了是可以再次读出改变后的值的。
```c
void main(){
    const int i = 0;
    int *j = (int *)&i;
    *j = 1;
    printf("%d,%d", i, *j);
    system("pause");
}
```

C++中，const变量是编译时的常量，可以向#define定义的常量一样使用。故C++中const变量的值在编译时就已经确定了，直接对cosnt变量进行了值的替换，因此当const变量的值改变时，const的变量值是不会得到更新的。

```cpp
#include<iostream>
using namespace std;
int main(void){
	const int i=0;
	int *j = (int *)&i;
	*j = 1;
	printf("%d,%d", i, *j);
	system("pause");
	return 0;
}
```
这几行代码在C和C++中都会改变const变量的值，只不过C++中const变量在编译的时候已经确定了，而C中的const变量可以在运行时改变后再次读取。以下代码核实了C++中的const变量确实被改变了。


### 17.在64位机器上sizeof(a) sizeof(b)大小分别是多少（A）
```cpp
char a[10];
char *b = (char*)malloc(10*sizeof(char));
```

+ 10 8
+ 20 4
+ 20  8
+ 10 4

```txt
b是一个char型的指针，在64位系统中sizeof（char*）=8 
a是一个char型的数组，在64位系统中sizeof（char）=1，共10值因此为10

64位系统中，指针占8个字节，32位系统中，指针占4个字节。
b是一个指向用malloc申请的大小为10*sizeof(char)的空间，在64位的系统中，指针占8字节
a是一个字符数组，大小为10*sizeof(char)，占10字节。
```

### 18.下面说法正确的是(A)
+ 一个空类默认一定生成构造函数,拷贝构造函数,赋值操作符,引用操作符,析构函数
+ 可以有多个析构函数
+ 析构函数可以为virtual,可以被重载
+ 类的构造函数如果都不是public访问属性,则类的实例无法创建

> D:注意单例模式

### 19.设有定义：`char *p;`，以下选项中不能正确将字符串赋值给字符型指针p的语句是（ABD）
+ `p=getchar();`
+ `scanf(“%s”,p);`
+ `char s[ ]=”china”;p=s;`
+ `*p=”china”;`

> 解析：

```txt
A选项 : 首先类型就不匹配
B选项 : p指针在定义的时候没有分配内存, 所以这行代码在运行的时候会报野指针错误
C选项 : 正确, 指针p指向数组s
D选项 : *p代表p指向内存的内容, 这里要使用p="china"才正确
```

### 20.在C++中，引用和指针的区别是（A）
+ 引用总是指向一个对象,指针可能不指向对象
+ 引用和指针都可以被重新赋值
+ 引用不能用const修饰，而指针可以
+ 引用创建时必须初始化，而指针则可以在任何时候被初始化