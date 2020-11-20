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

### 21.下面代码的输出是：(D)
```cpp
sizeof("hello")
strlen("world")
```

+ 5,5
+ 5,6
+ 6,6
+ 6,5

> 解析：

```txt
strlen 是函数，sizeof 是运算符。
strlen 测量的是字符的实际长度，以'\0' 结束，也就是说不算最后的'\0';
而sizeof 测量的是字符的分配大小,包括最后的'\0';
帮助记忆的话，可以理解成运算符更加底层一下，会输出真实的内存占用情况，而函数有封装，会处理成用户想要看到的内容
```

### 22.下面代码中，p和"hello,world"存储在内存哪个区域？（D）
+ 栈，堆
+ 栈，栈
+ 堆，只读存储区
+ 栈，只读存储区

> 解析：

```txt
（1）从静态存储区域分配：
内存在程序编译时就已经分配好，这块内存在程序的整个运行期间都存在。速度快、不容易出错，因为有系统会善后。例如全局变量，static变量等。
（2）在栈上分配：
在执行函数时，函数内局部变量的存储单元都在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限。
（3）从堆上分配：
即动态内存分配。程序在运行的时候用malloc或new申请任意大小的内存，程序员自己负责在何时用free或delete释放内存。动态内存的生存期由程序员决定，使用非常灵活。
如果在堆上分配了空间，就有责任回收它，否则运行的程序会出现内存泄漏，另外频繁地分配和释放不同大小的堆空间将会产生堆内碎块。
一个C、C++程序编译时内存分为5大存储区：堆区、栈区、全局区、文字常量区、程序代码区。
```

### 23.下面函数的执行结果是输出(B)
```cpp
char str[]=”xunlei”;
char *p=str;
int n=10;
printf(“%d,%d,%d\n”,sizeof(str),sizeof(p),sizeof(n));
```

+ 4，4，4
+ 7，4，4
+ 6，4，4
+ 6，6，4

解析：

```txt
sizeof(str),str是字符数组，所以第一个是7个字节
sizeof(p), str的首元素地址赋给指针p，指针总占4个字节
sizeof(n), int型整数，所以4个字节
```

### 24.下面程序的输出结果是（A）
```cpp
#include <iostream>
using namespace std;

int main() 
{
    char str1[] = "hello world";  
    char str2[] = "hello world";  

    const char str3[] = "hello world";  
    const char str4[] = "hello world";  

    const char* pstring1 = "hello world";  
    const char* pstring2 = "hello world";  

    cout << boolalpha << ( str1==str2 ) <<  ',' ; 
    cout << boolalpha << ( str3==str4 ) << ',' ;  
    cout << boolalpha << ( pstring1==pstring2 ) <<endl;

    return 0;
}
```

+ false,false,true
+ false,false,false
+ true,true,true
+ false,true,true

> 解析：

这个题主要是考察，变量在内存的存放的地点。感觉还可以加强一下变得难一些，比如比较地址的大小等等。
str1、str2、str3以及str4都是栈中定义的局部变量数组，并且进行了初始化，地址肯定会不一样。
而pstring1、pstring2则是指针，虽然本身在栈中，但是所指向的是一个字串常量。题中比较的就是所指向的地址，所以为true。

```cpp
#include<iostream>
using namespace std;
int main(void)
{
    char str1[] = "hello world";   //存放在栈中的数组
    char str2[] = "hello world";   //存放在栈中的数组

    const char str3[] = "hello world";  //存放在栈中的字符串常量
    const char str4[] = "hello world";  //存放在栈中的字符串常量

    const char* pstring1 = "hello world";   //本身在栈中，指向常量的指针
    const char* pstring2 = "hello world";   //本身在栈中，指向常量的指针     //显然二者所指向的地址一致

    int x = (int)pstring1;
    int y = (int)pstring2;                  //为了方便打印出指针所指向的地址

    cout << boolalpha << ( str1==str2 ) << endl;               //比较字串首地址      flase
    cout << boolalpha << ( str3==str4 ) << endl;               //比较字串首地址      flase
    cout << boolalpha << ( pstring1==pstring2 ) <<endl;        //比较指针所指地址    true

    cout << "str1=" << &str1 << ",";
    cout << "str2=" << &str2 << endl;

    cout << "str3=" << &str3 << ",";
    cout << "str4=" << &str4 << endl;

    cout << "pstring1=" << &pstring1 << ",";
    cout << "pstring2=" << &pstring2 << endl;                   //输出指针本身地址

    cout<<hex;
    cout << "pstring1=" << x << ",";
    cout<<hex;
    cout << "pstring2=" << y << endl;      //16进制输出指针所指地址

    return 0;
}

```

### 25.对C++中重载（overload）和重写（override）描述正确的有（ABD）
+ 重载是指在同一个类或名字空间中存在多个函数，它们的函数名相同，而函数签名不同
+ 重写是指在子类中实现一个虚函数，该虚函数与其父类中的一个虚函数拥有同样的函数签名
+ 虚函数不可以重载
+ 构造函数可以重载，析构函数可以重写

```txt
函数重载（overload）
函数重载是指在一个类中声明多个名称相同但参数列表不同的函数，这些的参数可能个数或顺序，类型不同，但是不能靠返回类型来判断。特征是：
（1）相同的范围（在同一个作用域中）；
（2）函数名字相同；
（3）参数不同；
（4）virtual 关键字可有可无（注：函数重载与有无virtual修饰无关）；
（5）返回值可以不同；

函数重写（也称为覆盖 override）
函数重写是指子类重新定义基类的虚函数。特征是：
（1）不在同一个作用域（分别位于派生类与基类）；
（2）函数名字相同；
（3）参数相同；
（4）基类函数必须有 virtual 关键字，不能有 static 。
（5）返回值相同，否则报错；
（6）重写函数的访问修饰符可以不同；

重定义（也称隐藏）
（1）不在同一个作用域（分别位于派生类与基类） ；
（2）函数名字相同；
（3）返回值可以不同；
（4）参数不同。此时，不论有无 virtual 关键字，基类的函数将被隐藏（注意别与重载以及覆盖混淆）；
（5）参数相同，但是基类函数没有 virtual关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）；
```

### 26.下面哪些函数不能被声明为虚函数（ABCD）
+ 构造函数
+ 静态成员函数
+ 内联函数
+ 友元函数

> 解析：以上几类函数都不可声明为虚函数：

+ 构造函数：虚函数是运行时绑定，需要对象，所以要先调用构造函数
+ 静态成员函数：只有一份大家共享
+ 内联函数：编译时就展开，而虚函数是运行时绑定
+ 友元函数：友元函数不能被继承，所以不存在虚函数

### 27.下面哪几种是 STL 容器类型(ABDE)
+ vector
+ set
+ multivector
+ multiset
+ array

> 解析：

```txt
C++11 STL中的容器
==================================================
一、顺序容器：
vector：可变大小数组；
deque：双端队列；
list：双向链表；
forward_list：单向链表；
array：固定大小数组；
string：与vector相似的容器，但专门用于保存字符。
==================================================
二、关联容器：
按关键字有序保存元素：（底层实现为红黑树）
map：关联数组；保存关键字-值对；
set：关键字即值，即只保存关键字的容器；
multimap：关键字可重复的map；
multiset：关键字可重复的set；
--------------------------------------------------------------------------------
无序集合：
unordered_map：用哈希函数组织的map；
unordered_set：用哈希函数组织的set；
unordered_multimap：哈希组织的map；关键字可以重复出现；
unordered_multiset：哈希组织的set；关键字可以重复出现。
==================================================
三、其他项：
stack、queue、valarray、bitset
```

### 28.下面的函数作用：将整型数组p中n个数据增大，代码的实现有错误，下面哪句话的表述是正确的？（A）
```cpp
void increment_ints (int p [ ], int n) 
{ 
  assert(p != NULL);  /* 确保p不为空指针 */ 
  assert(n >= 0);  /* 确保n不为负数 */ 
  while (n)  /* 循环n次. */ 
  { 
    *p++;          /* 增大p*/ 
    p++, n--;      /* p指向下一位，n减1 */ 
  } 
}
```

+ `*p++`使得p在解引用之前增大，应该改为`(*p)++`
+ 数组的值是一个不能改变的值，所以p不能直接被修改。应该使用一个和p相关联的指针来完成这个操作。
+ while循环的条件必须是一个布尔类型的表达式，表达式应该为n!=0.
+ p不应该定义为变长的数组，参数中不应该包含参数n。

> 解析：

```txt
A：同级运算符，自右向左，*p++相当于*(p++),正确的应该是(*p)++
B：数组名作为参数传递的时候将作为指针处理，可以通过指针名对值进行修改。
C：while循环的条件可以是表达式，也可以是值。非0为真，0为假
D：参数中传递数组中的长度是无效的，所以要把数组长度单独传送。
```

### 29.下列代码的运行结果是（B）
```cpp
void main()
{
    Stack S;
    Char x,y;
    InitStack(S);
    x='n';y='g';
    Push(S,x);Push(S,'i');Push(S,y);
    Pop(S,x);Push(S,'r');Push(S,'t');Push(S,x);
    Pop(S,x);Push(S,' s');
    while(!StackEmpty(S)){Pop(S,y);printf(y);};
        printf(x);
}
```

### 30.下面的代码输出是：（D）
```cpp
int main() {
    union Data {
        struct {
            int x;
            int y;
        } s;
        int x, y;
    } d;

    d.x = 1;
    d.y = 1;
    d.s.x = d.x * d.x;
    d.s.y = d.y + d.y;
    printf("%d %d\n", d.s.x, d.s.y);
}
```

+ 1 4
+ 4 4
+ 1 2
+ 4 8

> 解析：

```txt
union中的所有成员相对于基地址的偏移量都为零。d.x,d.y和d.s.x的起始地址都相同,共享内存空间，给任意一个变量赋值，其他两个变量也会赋相同的值。
d.x，d.y以及d.s.x都是前四个字节，所以他们的值永远相等，
d.x=1；///d.x=d.y=d.s.x=1;
d.y=2;///d.x=d.y=d.s.x=2;
d.s.x=d.x*d.x;///d.x=d.y=d.s.x=2*2=4;
d.s.y=d.y*d.y;///d.x=d.y=d.s.x=4+4=8;

更详细的解析：https://www.nowcoder.com/test/question/done?tid=39458166&qid=112253#summary
```

### 31.以下程序输出结果是(B)
```cpp
#include<iostream>
#include <cstring>

using namespace std;

class A {
public:
    virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }

    virtual void test() { func(); }
};

class B : public A {
public:
    void func(int val = 0) { std::cout << "B->" << val << std::endl; }
};

int main(int argc, char *argv[]) {
    B *p = new B;
    p->test();
    return 0;
}
```

+ A->0
+ B->1
+ A->1
+ B->0
+ 编译出错
+ 以上都不对

### 32.下面中哪两个可以在Demo的子类中使用：（AC）
```cpp
class Demo {
protected:
    int m1(int a, int b) {
        return 0;
    }
}
```

+ `public int m1 (int a, int b) { return 0; }`
+ `private int m1 (int a, int b) { return 0; }`
+ `private int m1 (int a, long b) { return 0; }`
+ `public short m1 (int a, int b) { return 0; }`

### 33.循环语句`while(int i=0 )i--;`的循环次数是（A）
+ 0
+ 1
+ 5
+ 无限次

> while ()里面是一个声明变量的语句，根本不会进入循环，而且在C语言中，定义变量都是放在最前面，总体来说，这个代码有错误

### 34.如下程序的执行结果(A)
```cpp
#include "stdio.h"

class A {
public:
    virtual void Test() {
        printf("A test\n");
    }
};

class B : public A {
public:
    void func() {
        Test();
    }

    virtual void Test() {
        printf("B test\n");
    }
};

class C : public B {
public:
    virtual void Test() {
        printf("C test\n");
    }
};

int main() {
    C c;
    ((B *) (&c))->func();
    ((B) c).func();
}
```

+ A
```txt
C test				
B test
```

+ B
```txt
B test
B test
```

+ C.
```txt
B test			
C test
```

+ D.
```txt
A test
C test
```

### 35.有如下代码，说法正确地是(B)
```cpp
struct A1{
    virtual ~A1(){}
};
struct A2{
    virtual ~A2(){}
};
struct B1 : A1, A2{};
int main()
{
 B1 d;
 A1* pb1 = &d;
 A2* pb2 = dynamic_cast<A2*>(pb1);  //L1
 A2* pb22 = static_cast<A2*>(pb1);  //L2
 return 0;
}
```

+ L1语句编译失败，L2语句编译通过
+ L1语句编译通过，L2语句编译失败
+ L1，L2都编译失败
+ L1，L2都编译通过

> 解析如下：

```txt
在类的转换时，在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的。在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。

向上转换，即为子类指针指向父类指针（一般不会出问题）；向下转换，即将父类指针转化子类指针。

向下转换的成功与否还与将要转换的类型有关，即要转换的指针指向的对象的实际类型与转换以后的对象类型一定要相同，否则转换失败。
```

### 36.以下C++代码会输出什么?(B)
```cpp
#include <iostream>

using namespace std;

class A {
    A() {}

    ~A() {}

    static int a;
};

int main() {
    cout << sizeof(A) << endl;
    return 0;
}
```

+ 0
+ 1
+ 4
+ 8

> 解析：

```txt
类的大小实际是指该类对象的大小。为类所有非静态数据成员的大小之和，需要内存对齐。不包括静态数据成员，不包括函数成员。
但若定义了虚函数，则需要加上虚指针的大小。类的大小不能为0，由前述规则计算出类大小为0时，实际大小为1。
本题中只有静态数据成员，没有非静态数据成员，所以大小为1
```

### 37.若main（）函数带 参数 ，参数个数最多是 (C)
+ 0
+ 1
+ 2
+ 3

> 解析：

```txt
Ｃ语言规定main函数的参数只能有两个，习惯上这两个参数写为argc和argv。因此，main函数的函数头可写为： 
main (argc,argv)
Ｃ语言还规定argc(第一个形参)必须是整型变量,argv( 第二个形参)必须是指向字符串的指针数组。
```

### 38.对于下面`char (*p)[16]`的声明描述正确的一项是(C)
+ p是长度为16的字符指针数组
+ p是包含16个字符的字符串
+ p是指向长度为16的字符数组的指针
+ p是长度为16的字符数组

### 39.当不同的类具有相同的间接基类时，（C）
+ 各派生类无法按继承路线产生自己的基类版本
+ 为了建立唯一的间接基类版本，应该声明间接基类为虚基类
+ 为了建立唯一的间接基类版本，应该声明派生类虚继承基类
+ 一旦声明虚继承，基类的性质就改变了，不能再定义新的派生类

> 解析：

```txt
派生列表中，同一基类只能出现一次，但实际上派生类可以多次继承同一个类。派生类可以通过两个直接基类分别继承自同一间接基类，也可以直接继承某个基类，再通过另一个基类再次继承该类。
但是，如果某个类派生过程中出现多次，则派生类中将包含该类的多个子对象，这种默认情况在很多有特殊要求的类中是行不通的。
虚继承就是为了应对这一情况而产生，虚继承的目的是令某个类做出声明，承诺愿意共享其基类。这样不论虚基类在继承体系中出现多少次，派生类中都只包含唯一一个共享的虚基类子对象。
```

### 40.若有以下类Z说明，则函数fStatic中访问数据a错误的是（C）
```cpp
class Z
{
    static int a;
public:
    static void fStatic(Z&);
};
int Z::a=0;
Z objZ;
```

+ `void Z::fStatic()  { objZ.a =1; }`
+ `void Z::fStatic()  { a = 1; }`
+ `void Z::fStatic()  { thisa = 0; }`
+ `void Z::fStatic()  { Z::a = 0; }`

> 解析：

```txt
本题考查类静态成员变量访问方法。静态成员变量又名类成员变量，为类所有，为所有类对象所有。
A选项：通过类对象访问，正确
B选项：通过类成员函数访问，正确，静态成员函数和非静态成员函数都可以直接访问
C选项：在静态成员函数中通过this指针访问，错误，this指针是指向当前类对象的指针，而fStatic是静态成员函数（是类的函数），没有this指针
D选项：通过类直接访问，正确
```

### 41.下面选项中关于编译预处理的叙述正确的是（B）
+ 预处理命令行必须使用分号结尾
+ 凡是以#号开头的行，都被称为编译预处理命令行
+ 预处理命令行不能出现在程序的最后一行
+ 预处理命令行的作用域是到最近的函数结束处

> 解析：

```txt
【解析】本题考查预编译的预编译处理命令行，预处理命令行不能以分号结尾，所以 A 选项错误，预处理命令行可以出现在程序的最后一行，预处理命令行作用域是整个文件。
```

### 42.下面程序的输出结果是（C）
```cpp
#include <stdio.h>

int main()
{ 
    int i, n = 0;
    float x = 1, y1 = 2.1 / 1.9, y2 = 1.9 / 2.1;

    for ( i = 1; i < 22; i++)
        x = x * y1;

    while ( x != 1.0 )
    {
        x = x * y2; n++;
    }

    printf( "%d\n", n );

    return 0; 
}
```

> 解析：浮点类型不能精确相等

### 43.在C++中，要实现动态联编，必须使用（D）调用虚函数。
+ 类名
+ 派生类指针
+ 对象名
+ 基类指针

> 解析：实现动态联编用父类指针或引用指向子类对象

### 44.请问运行Test函数会有什么样的结果？（D）
```cpp
void Test(void)
{
    char *str = (char *) malloc(100);
    strcpy(str, “hello”);
    free(str);
    if (str != NULL)
    {
        strcpy(str, “world”);
        printf(str);
    }
}
```

+ hello
+ world
+ helloworld
+ 未定义行为

> 解析：释放以后按照理论是不能访问的，如果这个时候访问并且往里面输入数据的话系统不能保证数据安全

### 45.经 过 以 下 语 句 定 义 后 , 表 达 式z+=x>y?++x:++y 的值为（C）？
```cpp
int x=1,y=2,z=3;
```
+ 2
+ 3
+ 6
+ 5

> 解析：赋值运算符<逻辑运算符<关系运算符<算数运算符

### 46.如下代码段中空白处应填入的代码正确的是：（A）
```cpp
void delete_obj(std::vector<Obj> &v_obj)
{
    std::vector<Obj>::iterator it = v_obj.begin();
    while(it != v_obj.end())
    {
        if(!it->isEmpty())
        {
            ______ //此处填代码
        }
       else
       {
            ++it;
       }
    }
}
```
+ it = v_obj.erase(it++);
+ v_obj.erase(it);
+ it=v_obj.erase(it);it++
+ v_obj.erase(it++);

> 解析：

### 47.请问下面的程序一共输出多少个“-”？（D）
+ 2
+ 4
+ 6
+ 8

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/1f6cc9c0ef354f86b1727c6c030a1a19
来源：牛客网

一共调用了6次printf，但是会输出8个-。因为父进程的输出缓冲也会被子进程复制
fork(); // i=0
    printf("-");    // buffer="-"
    fork(); // i=1
        printf("-");    // +1
    printf("-");
printf("-")
fork(); // i=1
    printf("-");    // +1
printf("-")
```

### 48.下列代码之后的结果为（D）
```cpp
#include <iostream>

using namespace std;

struct Base {
    int i;
    virtual int f() {
        cout << "a";
        return 1;
    }

    virtual const Base & f() const {
        cout << "b";
        return *this;
    }

    int g() {
        cout << "c";
        return 3;
    }
};

struct Derive: Base {
    int i;
    int f() {
        cout << "d";
        return 4;
    }

    const Base &f() const {
        cout << "e";
        return *this;
    }

    int f(int =0) {
        cout << "f";
        return 6;
    }

    virtual int g() {
        cout << "g";
        return 7;
    }
};

int main() {

    Derive d;
    const Derive d_const;
    Base b, *p = &d;
    const Base *p_const = &d_const;
    b.f();
    p->f();
    p->g();
    p_const->f();
    d_const.f();
    return 0;
}
```

+ abccf
+ acdff
+ abcde
+ adcee

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/c27d972a46514d45986496e864d24621
来源：牛客网

1.b.f(); 基类对象直接调用基类的f()函数，输出a
2.p->f(); 派生类对象赋给基类的指针，由于f()在基类中是虚函数，根据基类指针指向的对象进行调用，因此调用派生类的int f()输出d
3.p->g();基类中g()不是虚函数，调用基类的g()
4.p_const->f();常对象，又由于基类中声明为虚，同理用派生类中的函数
5.同理
```

### 49.下面的程序中， int32_t 表示一个有符号的 32 位整数，程序的入口是 main 函数，问最终 res 的结果是多少？(D)
> 链接：https://www.nowcoder.com/questionTerminal/b905e60905ce42e3a64a9f9007a5d1d1

```cpp
#include <iostream>

using namespace std;

int32_t  f(int32_t a, int32_t b) {
    while (a + b > 0) {
        a = a +1;
        b = b-1;
    }
    return a+b;
}

int32_t main() {
    int32_t res = f(1, 0);
    return 0;
}
```

+ –(2^31+2^30+…+2^2+2^1+2^0)
+ 0
+ -1
+ 程序会死循环

> 解析：char+char的结果会自动转化成int，所以(char)-128+(char)-127 = (int)-255。此时停止循环。但是int32+int32结果仍为int32，所以不会停止循环

### 50. 在32位机器上用gcc编译如下代码，求sizeof(A),sizeof(B)分别是多少。(C)
```cpp
class A {
    int a;
    short b;
    int c;
    char d;
};

class B {
    double a;
    short b;
    int c;
    char d;
};
```
+ 12 16
+ 12 12
+ 16 24
+ 16 20

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/ec319607d5c842e88f31d1aaf0582561
来源：牛客网

A  ----->     △△△△||△△==||△△△△||△===
B ----->    △△△△△△△△||△△==(short)△△△△(int)||△=======
其中△为数据存储，=为填充

链接：https://www.nowcoder.com/questionTerminal/ec319607d5c842e88f31d1aaf0582561
来源：牛客网

链接：https://www.nowcoder.com/questionTerminal/4bcbe5bbcb564d238d2f3d6e7dbb83ea?orderByHotValue=0&mutiTagIds=641_134&page=8&onlyReference=false
来源：牛客网
按照下面3个条件来计算：
1) 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；
备注：编译器在给结构体开辟空间时，首先找到结构体中最宽的基本数据类型，然后寻找内存地址能被该基本数据类型所整除的位置，作为结构体的首地址。将这个最宽的基本数据类型的大小作为上面介绍的对齐模数。
2) 结构体每个成员相对于结构体首地址的偏移量（offset）都是成员大小的整数倍，如有需要编译器会在成员之间加上填充字节（internal adding）；
备注:为结构体的一个成员开辟空间之前，编译器首先检查预开辟空间的首地址相对于结构体首地址的偏移是否是本成员的整数倍，若是，则存放本成员，
反之，则在本成员和上一个成员之间填充一定的字节，以达到整数倍的要求，也就是将预开辟空间的首地址后移几个字节。
3) 结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要，编译器会在最末一个成员之后加上填充字节（trailing padding）。
```

### 51.声明一个数组`int a[10];`问下面哪些不可以表示a[1]的地址？（B）
+ `&a[0] + 1`
+ `a+sizeof(int)`
+ `(int*)&a+1`
+ `(int*)((char*)&a+sizeof(int))`

> 解析：有图有真相，a+sizeof(int)，等价于a[4]的地址，因为数组a为int型，步长为4，+1就相当于向前进了4字节，等于a[1]地址，+4相当于进了16字节，等于a[4]地址

### 52.对于protected成员，下面说法错误的是:（A）
+ 基类可以访问从所有派生类造型（cast）成基类对象的protected成员
+ 从公有和保护继承的派生类继承的子类里可以访问基类的protected成员
+ 派生类可以定义一个同名的非protected成员
+ 派生类可以访问基类对象的公有protected成员

> 公有：所有成员皆可访问 保护：只有派生类可以访问 私有：只能类本身能访问 证明友元：不受限制。代码验证如下：

```cpp
class Base
{
protected:
    int ip=666;
    void ptshow()
    {
        cout<<"protected "<<ip<<endl;
    }
public:
    void show()
    {
        cout<<"public "<<ip<<endl;
    }
};
class Derive:public Base
{
public:
    void show()
    {
        cout<<"derive public "<<ip<<endl;
    }
    void ptshow()
    {
        cout<<"same name as Base::ptshow() "<<ip<<endl;
    }
    void myshow()
    {
        cout<<"my public show "<<ip<<endl;
    }
};
int main()
{
    //1. base
    Base b;
    //cout<<b.ip<<endl;//error: 不能访问自己的protected变量
    //b.ptshow();//error: Base::ptshow() is protected
    //b.show();//public 666  //可以访问protected变量。

    //2. derive
    Derive d;
    //cout<<d.ip<<endl;//error: Base::ip is protected
    //d.show();//derive public 666 //从派生类可访问protected变量
    //d.ptshow();//和Base的protected成员重名，ok

    //3. base pointer point to derive obj
    Base* x=new Derive();//没有虚函数的情况下，x的行为就是普通Base实例
    //x->ptshow();//error: 无法访问protected成员
    //x->myshow();//error: Base has no member named 'myshow'
    x->show();//public 666
    return 0;
}

```

### 53.以下叙述中正确的是（D）
+ 逻辑"或"（即运算符||）的运算级别比算术运算要高
+ C语言的关系表达式：0<x<10完全等价于: (0<x) && (x<10)
+ 逻辑"非"（即运算符!）的运算级别是最低的
+ 由&&构成的逻辑表达式与由||构成的逻辑表达式都有"短路"现象

> 【解析】 B 选项中， (x>0)&&(x<10) 的值是 1 或 0 ，条件是 x>0 并且 x <10 。但是 0<x<10 这种写法的结果任何时候都是 1 ；
 C 选项中，逻辑 " 非 " （即运算符 ! ）的运算级别是最高的； A 选项中，算术运算符优先级较高，关系和逻辑运算符优先级较低。因此 D 选项正确。

### 54.下面有关c++线程安全，说法错误的是？(C)
+ 线程安全问题都是由全局变量及静态变量引起的
+ 若每个线程中对全局变量、静态变量只有读操作，而无写操作，一般来说，这个全局变量是线程安全的；若有多个线程同时执行写操作，一般都需要考虑线程同步，否则的话就可能影响线程安全
+ c++标准库里面的string保证是线程安全的
+ POSIX线程标准要求C标准库中的大多数函数具备线程安全性

> 解析：

```txt
1.局部变量局部使用是安全的
为什么?因为每个thread 都有自己的运行堆栈，而局部变量是生存在堆栈中,大家不干扰。
2.全局原生变量多线程读写是不安全的  ， 全局变量是在堆(heap)中。
3.函数静态变量多线程读写也是不安全的。
4.volatile能保证全局整形变量是多线程安全的么？
不能。 volatile仅仅是告诫compiler不要对这个变量作优化，每次都要从memory取数值，而不是从register
5.InterlockedIncrement保证整型变量自增的原子性
写好多线程安全的法宝就是封装，使数据有保护的被访问到
安全性：

局部变量 > 成员变量 > 全局变量
```

### 55.下输出正确的是（B）
```cpp
class Base
{
    public:
    void virtual Func()
    {
        cout<<"Base"<<endl;
    }
};
 
class Derived : public Base
{
    public:
    void virtual Func()
    {
        cout<<"Derived "<<endl;
    }
};
 
int main ()
{
    Base* pBase = new Base();
    pBase ->Func();
    Derived * pDerived = (Derived*)pBase;
    pDerived->Func();
    delete pBase;
 
    pDerived  =  new Derived();
    pBase = pDerived;
    pBase->Func();
 
    delete pDerived
    return 0;
}
```
+ Base  Derived  Base
+ Base  Base  Derived
+ Base  Derived  Derived
+ Derived Base  Derived

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/814ce13c95ff439bab17f73ca5f0410a
来源：牛客网

选B，13好理解，对于2，强制类型转换时会将Base类型的数据所在的内存按照Derived类型格式解析和转换。pDerived解析得到的是pBase的虚函数表，相当于pDerived的vtbl虚函数表指针指向了pBase的虚函数表，故得到Base;
但这种强制转换比较危险，当访问某虚函数时子类存在而父类不存在时，就可能导致运行时出现访问错误，程序崩溃，而此时编译是正常的，因为指针的虚函数表是动态链接的。
```

### 56.下列代码运行出错，可能会是哪一行引起的?(B)
```cpp
void getMemory(char *p)  
{ 
 p = (char *)malloc(100);   // 1 
} 
  
int main(int argc, char const *argv[]) 
{ 
 char *str = NULL; 
 getMemory(str); 
 strcpy(str,"hello wrold");   //2 
 printf("%s\n", str);   //3 
 free(str);   //4 
} 
```
+ 1
+ 2
+ 3
+ 4

> 入getMemory的是str的拷贝，所以getMemory函数运行返回后，str仍为NULL，这样调用str自然会运行出错。要想使得传入的就是str指针本身，可以使用传引用的方式。

### 57.给定声明 const char * const * pp; 下列操作或说明正确的是?(A)
+ `pp++`
+ `(*pp)++`
+ `(**pp) = \\c\\;`
+ `以上都不对`

> 解析：

```txt
相当于
(char const) (* const) *pp
所以
**p是char型常量
*p是char const *型常量
p是char const *const型变量
```

### 58.以下代码共调用多少次拷贝构造函数：(D)
```cpp
Widget f(Widget u)
{  
   Widget v(u);
   Widget w=v;
   return w;
}
main(){
    Widget x;
    Widget y=f(f(x));
}
```
+ 1
+ 3
+ 5
+ 7

> 详细解释参考：https://www.nowcoder.com/questionTerminal/a0f69e79a60d45f2b441c7e92f8f6ad3

```txt
这道题目咋一看，觉得是调用了9次，而不是7次。可是实际运行发现确实只调用了7次。为什么呢？

我理解9次的原因在这里：形参u，局部变量v和w，return返回w这里还是有一次拷贝构造函数的调用的。你想，函数返回之后局部变量要被销毁，所以在返回之前必定有会新建一个临时对象出来，这时必然会再调用一次拷贝构造函数，这样分析，这个一个f（）函数就调用了4次拷贝构造函数，2次调用再加上主函数中给y的实例化，一共是9次才对！

从结果可以看出。我的分析肯定是错误的，错误发生在什么地方呢，我把主函数的调用注释掉，换一个写法，看结果再分析，再看这个运行图。

结果是一样的，都调用了7次。按上面的分析应该少 1 次（给 y实例化的那一次调用），这个问题的关键

就是出在这个return返回局部对象这里。通过单步调试，我发现是这么一回事：return之后一定会调用拷贝构造函数，这个返回的局部变量估计是编辑器直接优化给y了，和下一次的调用形参u。所以这里少了两次。（单步调试可以看得很清楚。）

拷贝构造函数调用的时机：
1、当用类的一个对象初始化该类的另一个对象时
2、 如果函数的形参是类的对象,调用函数时,进行形参和实参结合时. 
3、如果函数的返回值是类的对象,函数执行完成返回调用者时. 
4、需要产生一个临时类对象时
```

### 59.对于下面的说法，正确的是(F)。
> 链接：https://www.nowcoder.com/questionTerminal/1277288d00a64c1ca58736345fecbdab

+ 对于 struct X { short s; int i; char c; }，sizeof(X) 的值等于 sizeof(s) + sizeof(i) + sizeof(c)
+ 对于某个double变量 a，可以使用 a == 0.0 来判断其是否为零
+ 初始化方式 char a[14] = "Hello, world!"; 和初始化方式 char a[14]; a = "Hello, world!"; 的效果相同
+ 在gcc编译器下，对于 int i = 3; printf("%d %d", ++i, ++i)，运行输出为：4 5
+ 选项A、B、C、D中至少有两个是正确的
+ 以上选项均不正确

> 解答：链接：https://www.nowcoder.com/questionTerminal/1277288d00a64c1ca58736345fecbdab

```txt
A结构体要按高位对齐，int占四个字节，short占两个，char占一个 字节，所以4+4+4=12；
B要判断一个双精度浮点数：if( abs(f) <= 1e-15 )
C数组初始化两种方式：一种逐个赋值 char a[14] ={‘H’，‘e’,'l','l','o'}；另一种 char a[14] = "Hello, world!"
D选项，函数的参数是从右向左压栈的，输出时从栈顶开始，相当于: int i = 3;  ++i; ++i; printf("%d,%d",i,i);所以是 5，5；
再举一个例子，int i = 1; printf("%d,%d", i += 2, i *= 3); 在输出i之前先进行了i *= 3和 i += 2；最终i = 5；所以结果是5，5；
```

### 60.下面说法正确的是：(C)
> https://www.nowcoder.com/questionTerminal/3327439779e146dc9035b0977d9469eb
```cpp
signed char a=0xe0;
unsigned int b=a;
unsigned char c=a;
```
+ (a>0 )&&(b>0)为真
+ c==a 为真
+ b的16进制为0xffffffe0
+ 都不对

> 解析：

```txt
a的值为-32，所以a<0.
相反，c的值为224，大于0.
b的16进制表示为ffffffe0

有符号数最高位为1，所以a为负数；
负数原码转补码是符号位不变，其他各位取反，然后加1；
无符号数的原，反，补码一样
补码转原码：a = 0xe0的补码是1110 0000，所以a的原码是1010 0000 = -32
c是无符号数1110 0000就是它的原码，所以c = 224
signed char转signed int: 将a的原码拓展为32位编码1000 0000 0000 0000 0010 0000
有符号负数原码转补码为，之后signed int转unsigned int同理：1111 1111 1111 1111 1110 0000 = 0xffffffe0 = b。
```

### 61.为避免运算过程中出现整型溢出可以考虑的办法有（BC）
+ 将运算结果和可以表示的最大整数进行比较
+ 检测符号位的变化
+ 将计算结果减去加数看是否与另一加数相等
+ 比较参数的长度

```txt
链接：https://www.nowcoder.com/questionTerminal/7d7844f2443c46b98a7f10cab1174e0c
来源：牛客网

选项1 ： 运算结果进行比较的话，已经溢出导致结果变化，去比较也为时已晚。 所以不正确
选项2 ： 检测符号为变化可以防止符号溢出，正确。
选项3 ： a+b = c   c - a != b 则c溢出 正确
选项4 ： 参数长度    0000000000000000000000000 这个长度算溢出么 不正确
```

### 62.下列代码段的打印结果为（A）（注：└┘代表空格）
```cpp
#include <stdio.h>

void main(void) {
    char ac[] = "Hello World! C Program", * p;

    for (p = ac + 6; p < ac + 9; p++) {
        printf("%c", * p);
    }
}
```

+ Wor
+ o W
+ └┘Wo
+ o Wor

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/dedf7f3c0e09454e9c951fb8307289a4
来源：牛客网

p=ac+6表示把ac[6]的地址赋给指针p，p<ac+9表示p只能访问到ac[9]之前的地址，p++表示指针迭代，*p调用该指针指向的数即地址对应的数
代码的意思就是输出从ac[6]到ac[8]的一段字符串
```

### 63.以下代码是否完全正确，执行可能得到的结果是(C)。
```cpp
class A{
   int i;
};
class B{
   A *p;
public:
   B(){p=new A;}
   ~B(){delete p;}
};
void sayHello(B b){
}
int main(){
   B b;
   sayHello(b);
}
```
+ 程序正常运行
+ 程序编译错误
+ 程序崩溃
+ 程序死循环

> 为了清晰可见，我们从新把题目代码码一遍：

```cpp
class A{
   int i;
};
class B{
   A *p;
public:
   B(){p=new A;}
   ~B(){delete p;}
   /*
   B(const B& ths){
	   p = ths.p;
   }*/
};
void sayHello(B x){
}
int main(){
   B b;
   sayHello(b);
}
```

这里的错误原因是编译器在生成default copy construction的时候使用的bitwise copy语义，也就是只是简单的浅拷贝。 上面被注释掉的程序就是编译器自动添加的部分。 从而导致在sayHello中向参数x传递值时，调用了bitwise copy的拷贝构造函数，使得x对象和b对象中的值完全一致，包括p指针的值，在x离开作用域（也就是sayHello函数结束），x发生析构，调用delete 销毁了指针p，同时在main函数结束的时候，析构b时又会调用一次delete删除指针p。
也就是本程序会delete一直已经被delete 的指针。可以做如下改进，来修复程序：

```cpp
class A{
   int i;
};
class B{
   A *p;
public:
   B(){p=new A;}
   ~B(){delete p;}
   B(const B& other){
	   p = new A;		//构建新的指针
	   *p = *(other.p);	//将指向的内容复制，依然指向不同的位置
   }
};
void sayHello(B b){
}
int main(){
   B b;
   sayHello(b);
}
```

如上，在B中添加copy 构造函数,实现深拷贝即可

### 64.下面程序的功能是输出数组的全排列,选择正确的选项,完成其功能。(B)
```cpp
void perm(int list[], int k, int m)
{
    if (    )
    {
        copy(list,list+m,ostream_iterator<int>(cout," "));
        cout<<endl;
        return;
    }
    for (int i=k; i<=m; i++)
    {
        swap(&list[k],&list[i]);
        (    );
        swap(&list[k],&list[i]);
    }
}
```
+ `k!=m 和 perm（list，k+1，m）`
+ `k==m 和 perm（list，k+1，m）`
+ `k!=m 和 perm（list，k，m）`
+ `k==m 和 perm（list，k，m）`

### 65.执行下列程序后,其输出结果是（C）
```cpp
main() {
    int a = 9;
    a += a -= a + a;
    printf("%d\n", a);
}
```
+ 18
+ 9
+ -18
+ -9

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/1e5530882df140d3a152c6420e9cbfba
来源：牛客网

根据运算优先级可将上面式子分解成如下：
1、a -= (a+a);
2、a += （第一个式子的结果）;
第一个式子的结果 a = -9;
故  2中 a = a + (-9) = -9 + (-9) =  -18;
```

### 66.已知int x=5;，执行语句`x+=x-=x*x;`后，x的值为（C）
+ 25
+ 40
+ –40
+ 20

> 先算x-＝x*x，得出x=5-5*5,x=-20;再算x+=x;得出x=-20-20,x=-40

### 67.关于这段代码，下列说法正确的是(B)
```cpp
#define SIZE_20M (20*1024*1024)
void func_a()
{
    char *temp = malloc(SIZE_20M)
    return;
}
void func_b()
{
    char temp[SIZE_20M];
    //...do something using temp
    return;
}
```

+ func_a 获得临时内存的方式效率通常更高。
+ func_b 使用了太多的栈，程序可能会在运行时候崩溃。
+ func_b 存在内存泄露
+ func_a 和func_b 分配的内存会自动初始化0

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/11a1f270d36846b49c6dbe49f172fc3f
来源：牛客网

A   func_a()动态分配的数据位于堆区，func_b()的temp位于栈区，栈区的执行效率高于堆区，故func_b()效率高
C  func_b()中没有动态分配的内存，不存在泄露问题
D  都不会自动初始化为0，只有全局变量或者static变量会初始化为0
B  栈的空间一般为2M，分配太多栈空间程序肯定会崩溃
```

### 68.如下代码段，哪种描述是正确的（B）
```cpp
#include <iostream>

using namespace std;

class A {};
void f(const A ** p) {}
void g(const A * const * p) {}
void k(const A*& p){}

int main() {
    const A * ca = new A();
    A *a = new A();
    A** p = &a;
    k(ca); // 1
    f(p); // 2
    g(p); // 3
}
```
+ 全部正确
+ 2错，1,3正确
+ 1,2错，3正确
+ 1正确，2,3,错

> 解析：

```txt
链接：https://www.nowcoder.com/questionTerminal/918f550b51df44e8b88e66ef87882b58
来源：牛客网

1：const A*&p形参限定的是A*的内容，ca刚好限定了A*指向的内容。
2错误点：首先，p是一个二级指针，且指向是A*，根据题目给的信息，A* 指向的内容是可修改的，
但是f()函数中的形参 const A** p 的意思就是 p的指向可以改，A*的指向也可以改，但是A*指向的内容不可更改，参数转换出错，所以编译是不通过的。
3：g(const A* const* p) 其实左边的const是没有实际意义的，const限定的是*A的指向，并没有限定*A指向的内容，和参数p是刚好匹配的
```

### 69.下列关于new delete 与malloc free 的联系与区别描述正确的有?(BC)
+ 都是在栈上进行动态的内存操作
+ 用malloc函数需要指定内存分配的字节数并且不能初始化对象，new 会自动调用对象的构造函数
+ delete 会调用对象的destructor，而free 不会调用对象的destructor
+ 以上说法都不正确

> 解析：

```txt
A:都是在堆上取得内存。
BC的详细解释可以参考一下这篇博文，作者写的很详细。http://blog.csdn.net/hazir/article/details/21413833
```

### 70.以下程序运行后的输出结果是（A）
```cpp
int main() {
    int a = 1, b = 2, m = 0, n = 0, k;

    k = (n = b < a) && (m = a);
    printf("%d,%d\n", k, m);

    return 0;
}
```
+ 0,0
+ 0,1
+ 1,0
+ 1,1

### 71.下面程序的输出结果是（B）
```cpp
#include <iostream>

using namespace std;
class MD {
    protected:
        float miles;
    public:
        void setDist(float d) {
            miles = d;
        }
    virtual float getDist() {
        return miles;
    }
    float square() {
        return getDist() * getDist();
    }
};

class FeetDist: public MD {
    protected: float feet;
    public: void setDist(float);
    float getDist() {
        return feet;
    }
    float getMiles() {
        return miles;
    }
};

void FeetDist::setDist(float ft) {
    feet = ft;
    MD::setDist(feet / 2);
}

int main() {
    FeetDist feet;

    feet.setDist(8);
    cout << feet.getDist() << "," << feet.getMiles() << "," << feet.square() << endl;

    return 0;
}
```

+ 8,4,16
+ 8,4,64
+ 8,8,64
+ 其他几项都不对

> 解析

```txt
链接：https://www.nowcoder.com/questionTerminal/c72c1799bca34a09a6de0a3f5581c396
来源：牛客网

注意一点MD::setDist()函数调用。此时是没有父类的对象的，调用函数后设置的变量值当然也不属于父类对象。那他属于谁呢，没错他是子类继承自父类的变量，属于子类对象。
本题其实漏掉了一个考点，如果同时创建一个父类对象并给父类对象的成员变量miles赋值。此时同时输出父类对象的getDist(),和子类的getMiles()函数，通过对比能更直观的理解继承中子类继承全部的父类内容。
```

### 72.下面程序的执行结果：(E)
```cpp
class A{ 
    public: 
        long a; 
}; 
class B : public A { 
    public: 
        long b; 
}; 
void seta(A* data, int idx) { 
    data[idx].a = 2; 
} 
int main(int argc, char *argv[]) { 
    B data[4]; 
    for(int i=0; i<4; ++i){ 
        data[i].a = 1; 
        data[i].b = 1; 
        seta(data, i); 
    } 
    for(int i=0; i<4; ++i){ 
         std::cout << data[i].a << data[i].b; 
    } 
    return 0; 
}
```

+ 11111111
+ 12121212
+ 11112222
+ 21212121
+ 22221111

```txt
链接：https://www.nowcoder.com/questionTerminal/c85f9e15e6a4410a930581ae12b9a341
来源：牛客网

这道题应该注意 指针类型加减 时步长的问题。
A 大小为 4
B 大小为 8
那么：
void seta(A* data, int idx) {
    data[idx].a = 2;
}
由于传入的实参为B类型，大小为8，而形参为A类型，大小为4
data[idx] 取 data + idx 处的元素，这时指针 data加1 的长度不是一个B长度，而是一个A长度，或者说是1/2个B长度。这时该函数中 data[0~3] 指向的是原 data[0].a,data[0].b,data[1].a,data[1].b, 
由于隐式类型转换的缘故，data[0].a, data[0].b,data[1].a,data[1].b 处的值全部由于 data[idx].a = 2; 操作变为 2。
这道题如果改为void seta(B* data, int idx)，那么形参中data指针加1步长为8，结果就是21212121。但是由于步长为4，所以结果就是 22221111。
```

### 73.有以下程序程序运行后的输出结果是？(B)
```cpp
#include < stdio. h > 
main ( )
{ 
    int a [ 3 ] [ 4 ] = { 1,3,5,7,9,11,13,15,17,19,21,23 } , (*p) [4] = a , i , j , k = 0 ;
    for ( i =0 ; i < 3 ; i + + )
    for ( j =0 ; j < 2 ; j + + ) 
        k = k + * ( * ( p+i )+j );
    printf ( "%d" , k );
}
```

+ 40
+ 60
+ 80
+ 100

```txt
链接：https://www.nowcoder.com/questionTerminal/e913f4aaf41840c68c97cec70741c8e8
来源：牛客网

本题答案应为 60

int (*p)[4]= a；说明 p是一个指针数组，长度为4，存储的是二维数组每行的地址。
p指向a的首地址 &a[0][0].
*(p+i) 相当于p[i]，p[i]存储的是二维数组a的i行的数据地址。即p[i]=&a[i][0]；
*(p+i)+j 存储的是a[i][j]的地址。*(*(p+i)+j)即是a[i][j]的值。
根据i j循环。i<3,j<2，即是取二维数组三行的前两列的值的总和。
1+3+9+11+17+19=60
```

### 74.已知ii，j都是整型变量，下列表达式中，与下标引用X[ii][j]不等效的是（BC）。
+ `*（X[ii]+j）`
+ `*(X+ii)[j]`
+ `*(X+ii+j)`
+ `*(*(X+ii)+j)`

```txt
B应该也是错误的，
由于[]的优先级高于*,因此，相当于对地址（X+ii）[j]取值，
如果B改为（*（X+ii））[j]就对了
```

### 74.32位系统下下面程序的输出结果为多少？(B)
```cpp
void Func(char str_arg[100])
{
       printf("%d\n",sizeof(str_arg));
}
int main(void)
{
     char str[]="Hello";
     printf("%d\n",sizeof(str));
    printf("%d\n",strlen(str));
    char*p=str;
    printf("%d\n",sizeof(p));
    Func(str);
}
```
+ 5 5 4 4
+ 6 5 4 4
+ 6 5 6 4
+ 5 5 5 100

```txt
链接：https://www.nowcoder.com/questionTerminal/edc7169f19274d4a9d486959cba68f3e
来源：牛客网

输出结果为：6 5 4 4
对字符串进行sizeof操作的时候，会把字符串的结束符"\0"计算进去的，进行strlen操作求字符串的长度的时候，不计算\0的。
数组作为函数参数传递的时候，已经退化为指针了，Func函数的参数str_arg只是表示一个指针，那个100不起任何作用的。

链接：https://www.nowcoder.com/questionTerminal/edc7169f19274d4a9d486959cba68f3e
来源：牛客网

都是什么栏解析
第一个长度，是实际数组的长度5个字符，一个隐式的‘\0’编译会分配6个字节
第二个长度，标准的C库函数，返回字符串实际长度，那么是5个字符
第三个长度，是一个指针的长度，就是计算机系统的地址长度，32位机器 4字节
第四个和第三个同理，形参传递数组，传递的是数组首地址
```

### 75.64位系统下有 `char ** p[4];` 请问 `sizeof p` 的值是多少()
+ 8
+ 16
+ 32
+ 64

```txt
链接：https://www.nowcoder.com/questionTerminal/77372e53971045e2ad576be1306188a8
来源：牛客网

p 是个数组，所以 sizeof(p) 返回数组的占用大小，64 位情况下
【char **p[4] 】 表示 【char** 数组】 返回 4 * 8 = 32
【char *(*p)[4] 】 表示 【指向 char* 数组的指针】 返回 8
【char (**p)[4] 】 表示 【指向 char 数组的指针的指针】 返回 8
```

### 76.假定CSomething是一个类，执行下面这些语句之后，内存里创建了__6__个CSomething对象。
```cpp
CSomething a();
CSomething b(2);
CSomething c[3];
CSomething &ra = b;
CSomething d=b;
CSomething *pA = c;
CSomething *p = new CSomething(4);
```

> 解析

```cpp
CSomething a();  //只是个函数声明
CSomething b(2); // +1
CSomething c[3]; // +3，对象数组
CSomething &ra = b; // 引用，没有新构造
CSomething d=b; // +1，调用拷贝构造函数
CSomething *pA = c; // 只是给指针赋值
CSomething *p = new CSomething(4); // +1，构造并给指针赋值
```

### 77.关于C++中的友元函数说法正确的是（BC）
+ 友元函数需要通过对象或指针调用
+ 友元函数是不能被继承的
+ 友元函数没有this指针
+ 友元函数破环了继承性机制

> 解析：

```txt
友元函数是一种在类外定义，在类内特殊声明(加关键字friend)，并且可以在类外访问类的所有成员的非成员函数。友元函数相对于普通函数，增加了访问类成员的权利。

A、友元函数可以像普通函数一样直接调用，不需要通过对象或指针；
BC、友元函数不是成员函数，所以不能被继承，也同样没有this指针；
D、由于友元函数和普通函数的区别仅仅是具有访问类成员的权利，和继承性机制没有关系
```

### 78.求输出结果 (A)
```cpp
int a[2][2][3]= { {{1,2,3},{4,5,6}},{{7,8,9},{10,11,12}}};
int *ptr=(int *)(&a+1);
printf(“%d %d”, *(int*)(a+1), *(ptr-1));
```
+ 7 12
+ 1 6
+ 1 3
+ 7 9

```txt
1. &a+i = a + i*sizeof(a);  
2. a+i = a +i*sizeof(a[0]);   
```

### 79.能用友元函数重载的运算符是（A）
+ `+`
+ `=`
+ `[]`
+ `->`

> C++规定=，[ ]，()，->这四个运算符只能被重载为类的非静态成员函数，其他的可以被友元重载，主要是因为其他的运算符重载函数都会根据参数类型或数目进行精确匹配，这四个不具有这种检查的功能，用友元定义就会出错。

### 80.X定义如下，若存在X a; a.x=0x11223344;则a.y[1]的值可能为（BC）
+ 11
+ 22
+ 33
+ 44

> 解析：

```txt
union内的类型共享一段内存，大小按照最大的类型算
举个例子，比如数字0x12 34 56 78在内存中的表现形式为：
1)大端模式：

低地址 -----------------> 高地址
0x12  |  0x34  |  0x56  |  0x78
2)小端模式：

低地址 ------------------> 高地址
0x78  |  0x56  |  0x34  |  0x12
可见，大端模式和字符串的存储模式类似。
--------------------- 
作者：ce123 
来源：CSDN 
原文：https://blog.csdn.net/ce123_zhouwei/article/details/6971544 
版权声明：本文为博主原创文章，转载请附上博文链接！
大端是数据低位存储在内存高位,在四个字节上按照从高到低排列0x11223344。所以y[0]=0x11 y[1]=0x22.....
小端是数据低位存储在内存低位,在四个字节上按照从高到低排列0x11223344。所以y[0]=0x44 y[1]=0x33.....

两个考点：
1.联合体union是共用存储空间的
2.大端模式和小端模式数据的存储
```

### 81.哪些因素可能会影响到一个类的大小(ACF)
+ 成员个数
+ 函数个数
+ 是否有虚函数
+ 虚函数个数
+ 静态变量个数
+ 对齐方式

### 82.以下代码段执行后的输出结果为(D)
```cpp
public class Test {
    public static void main(String args[]) {
        int x = -5;
        int y = -12;
        System.out.println(y % x);
    }
}
```
+ -1
+ 2
+ 1
+ -2

> 解析：

```txt
C++整数取余，符号只与前面的数字有关。

|小| % |大| = |小| 符号同前面数字    |大| % |小| = |余| 符号同前面数字

3%4 = 3 ； -3%4 = -3 ； -3%-4 = -3 ； 3%-4 = 3；

5%3 = 2 ； 5%-3 = 2  ；-5%-3 = -2 ； -5%3 = -2；
```

### 83.若有以下类W说明，则函数fConst的正确定义是（A）
```cpp
class W {
    int a;
    public:
        void fConst(int & ) const;
};
```
+ `void W::fConst( int &k )const  { k = a; }`
+ `void W::fConst( int &k )const  { k = a++; }`
+ `void W::fConst( int &k )const  { cin >> a; }`
+ `void W::fConst( int &k )const  { a = k; }`

> 解析

```txt
这道题目考的是const关键字，类的方法后面加了const后，该方法的实现中不能修改类的成员。即不能修改类成员a选项中，只有选项A，没有修改类成员a的值
```

