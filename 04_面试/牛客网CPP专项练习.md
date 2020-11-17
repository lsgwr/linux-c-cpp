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