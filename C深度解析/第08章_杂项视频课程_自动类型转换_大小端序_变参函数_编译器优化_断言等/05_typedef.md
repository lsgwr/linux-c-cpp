# 4. typedef

## 4.1 作用

typedef用来给类型重命名，然后就可以使用重命名的类型来定义变量了，比如：

```c
typedef float fl; 
typedef unsigned int uint;

fl a; 		//等价于 float a
uint b;		//等价于 unsigned int b
```

疑问：重名后，原有类型还有效吗？  
答：当然有，float和unsigned int虽然被重命名了，但是float和unsigned int依然有效。 

提问：typedef uint u32可以吗？  
答：当然可以，我们在不少c源码中会经常见到这种多次重命名的情况，至于为什么要这么做，我们暂不解释。
	
## 4.2 typedef重命名的目的

目的有两个：

### （1）简化名字

比如将unsigned int简化为uint。

### （2）提高代码可移植性

如何提高可移植性，后面再介绍  

在一般情况下，使用typedef目的基本都是为了简化类型名字  
		
## 4.3 typedef使用举例

### （1）普通类型

```c
int in;
unsigned int uint;
float fl;
double dl;

// 如果不加typedef的话，in、uint、fl、dl都是变量，但是加了typedef后，都是新类型名。

typedef int in;
typedef unsigned int uint;
typedef float fl;
typedef double dl;
			
```

### （2）结构体、联合体、枚举

同样的，如果不使用typedef的话就是变量，否则就是新类型名

```c
struct Student
{
    ...
}Stu;	 //Stu：变量

struct Student Stu; //Stu：变量

typedef struct Student
{
    ...
}Stu;	 //Stu：新类型名

typedef struct Student Stu; //Stu：新类型名

Stu stu1; //与struct Student stu效果是一样的


typedef enum Week
{
    SUM,
    MON,
    ...
}Wk;

Wk weekday = SUM;
```


联合体也是一样的，这里不再啰嗦。
		
		
### （3）指针类型

```c
int *intp;
struct Student *stup;
typedef struct Student
{
    ...
}*stup;	 //也是可以的，stup：新类型名

void (*funp)(int, float);
int (*bufp)[10];
```

没有typedef时，全部是指针变量，但是加了typedef之后，就为指针类型  

```c
typedef int *intp;
typedef struct Student *stup;

typedef void (*funp)(int, float);
typedef int (*bufp)[10];

intp p1; //等价于int *p1
stup p2; //等价于struct Student *p2
funp p3; //等价于void (*p3)(int, float)
bufp p4; //等价于int (*p4)[10];
```
		
		
#### （4）数组

typedef的用法很灵活的，它也可以用在数组上，比如：

```c
int bufType[10];   //此时bufType一个数组，但是加上了typedef后，就是一个类型。

typedef int bufType[10]; 

bufType buf; //等价于int buf[10];
```
		
## 4.2 typedef与#define

其实#define也可以用来对类型进行“重命名”，不过我们这里的重命名是打了“引号”的，与typedef之间有区别。

### 4.2.1 使用#define来重命名

比如：

```c
#define uint unsigned int

uint a; //与unsigned int a的效果是一致的。
```

不过大家也发现了typedef的顺序和#define的顺序刚好相反，很多同学总是容易搞混淆它们顺序，我们建议大家只记住其中一个，然后另一个的顺序刚好相反，这样就不会混淆了  

### 4.2.2 typedef与#define的区别

二者的区别就来自于各自实现原理的不同，#define只是简单的宏替换，而typedef才是真正意义上的重命名。
		
比如上面的uint就是一个宏，uint a进行宏替换后，最终面貌还是unsigned int a，但是typedef重命名的类型名不是宏，不存在宏替换的问题，正是由于二者的这点不同，导致它们之间有很大区别。

接下来我们具体的对比一下它们的区别：
		
#### （1）各自的效果不一样

```c
typedef char * charp; 		//不要忘了加分号;
charp p1, p2;  				//等价于char *p1, *p2;
```

```c
#define charp char *  
charp p1, p2; 					//进行宏替换后，最终其实为char *p1, p2
```

二者明显不一样。
		
#### （2）#define有局限

```c
typedef void (*funp)(int, double)
```

像函数指针和数组指针类型，只能使用typedef来重命名，还真没办法使用#define来重命名。

		
#### （3）各自的处理阶段是不同的

我们在第一章详细的介绍过编译链接的四个阶段：
+ 第一阶段：预编译
+ 第二阶段：编译
+ 第三阶段：汇编
+ 第四阶段：链接

宏：在预编译阶段处理，将宏替换换真正的“宏体”
类型：在编译阶段处理

typedef重命名的类型名与原生的类型名只是名字不同而已，但是它们之前没有任何区别，因此

```c
typedef char *charp;
charp p1, p2; 
```
charp在编译阶段被处理。

```c
#define charp char *  
charp p1, p2; 
```
charp为宏定义，在"预编译"阶段，charp宏会被展开为原生类型`char *`，然后`char *`会在编译阶段被处理
			
					
#### （4）我们的建议

从前面的分析可以看出，使用#define来定义“新类型名”缺点不少，当我们自己写代码时，我们不建议使用#define来重命名“新类型名”，而是建议使用typedef来实现，typedef更规范。
			
当然，虽然我们建议都使用typedef，但是实际上在有些c源码中，有时候还是会使用#define来重命名，当大家看到#define这种重命名方式时不要感到惊讶。
		
		
## 4.3 typedef与const

我们直接举例介绍。
	
### （1）例子1

```c
typdef const int cstInt;

cstInt a = 10; //等价于const int a  或者 int const a
```

通过简化的“新类型名”cstInt，就可以定义出一个const的int变量。

```c
typdef int *const cstIntp1;
cstIntp1 p; //等价于int *const p


typdef  int const  *cstIntp2; //等价于typdef const int *cstIntp2;
cstIntp2 p; //等价于int const *p 或者const int *p


typdef int const * const cstIntp3;
cstIntp3 p;	//int const * const p
```
		
		
### （2）例子2

```c
typedef int *intp;

const intp p; 
intp const p;
```
以上这两种都等价于`int *const p`;

如果想得到`int const *p`，只能
```c
typdef int const *cstIntp;
cstIntp p; 
```
	

				
## 4.3 `***_t`类型作用

我们在C库、在OS API、Linux内核源码中，经常看到`***_t`的类型，比如：
· Linux OS API： time_t time(time_t *tloc)
	time_t

· posix c线程库函数：
```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

pthread_t、pthread_attr_t

· Linux OS API：
  ```c
  ssize_t write(int fd, const void *buf, size_t count);
  ssize_t、size_t
  ```

· c标准库函数：`void *malloc(size_t size);`

· 等等

很多同学一直搞不清楚这种`***_t`类型是怎么回事，它们到底有什么作用，我们这里就来介绍这个问题。


## 4.4 `***_t`怎么来的

这`***_t`类型都是通过typedef重命名后得到的，比如以time_t为例

```c
typedef time_t long int;
```

我们将time_t的typedef的过程简化了，实际上中间还经过了多次typedef，我们直接将其省略了。
以后凡是看到`***_t`类型，你就知道这个typedef后的类型，尾缀t就是typedef的意思。

实际上_t只是命名习惯，不加_t也无所谓，但是在c库、c框架、c语言的OS内核代码中，都习惯于给新类型名加_t。
事实上我们自己在重命名时不建议使用_t结尾，因为这样容易和c库等源码中的`***_t`类型搞混。
		
## 4.5 c库、Linux内核代码中的***_t有什么用		

我们这里举例说明。

### 4.5.1 直接使用原生类型的弊端

#### （1）例子

我们这个例子只是一个示例的例子，主要是为了说明其中的道理，大家不要纠结于其中细节的合理性。

```c
//windows环境的代码
long int InitFun(long int arg)
{
	...
}
```

这个代码要用到32位的整形，我们假设在Windows这边long int为32，而在Linux这边int才为32位，如果这个从windows这边迁移到Linux这边的话，我们需要将long int修改为int，如果你不改这个类型的，因为类型大小的不同，可能会给巨大隐患，所以必须修改类型：
```c
int InitFun(int arg)
{
    ...
}
```

如果代码是非常庞大，而且全部使用的都是原生类型的话，移植这些代码到不同平台上（比如不同的OS、不同CPU）时，就类型这个玩意，你就需要进行海量的改动，这个是非常痛苦的。

当然如果是如下是那种情况的话，还好。
+ （1）代码不涉及跨平台（只在一个平台上使用）
+ （2）代码体量很小，改起来不费劲
+ （3）代码对类型大小的变化不敏感
     一般来说类型大小变了，肯定会导致变量空间大小的变化，导致出现数据溢出等的问题，最后使得程序不能正常工作。

		
#### （2）解决原生类型的移植问题	

定义一个.h，比如type.h

```c
#ifnedf H_TYPE_H
#define H_TYPE_H

#define __WINDOWS 
//#define __LINUX

#if defined(__WINDOWS)
    typedef  	int32_t long int

#elif defined(__LINUX)
    typedef 	int32_t int;

#endif

...
...
...

int32_t Init_Fun(int32_t arg)
{
    ...
}
#endif	
```

在代码中只需要使用`***_t`即可，当代码需要移植到不同平台时，只要定义`__WINDOWS`或作者`__LINUX`宏，就可以通过条件编译来选择32int_t到底是long int还是int，给移植带了极大的便利。

对条件编译不了解的同学，请看第2章《预编译》，我们有详细介绍。	


c库函数、c实现的OS（大多数OS都是c写的）、c框架代码，都是大型c软件，而且大多都涉及到跨平台的问题，
比如：
· c标准库：在各大OS（windows/linux/安卓）上都能使用，涉及到跨OS
· linux OS：能够在ARM cpu上运行，也能在POWRPC的cpu上运行，涉及跨芯片

以上这些跨平台的代码都是海量级别的，所以如果没有`***_t`这种措施的话，跨平台移植时，就类型这一样就够折腾的。

## 4.6 我们自己的c应用代码，应该如何对待“原生类型”的使用呢

### 4.6.1 如果不涉及跨平台

在这种情况下，我们可以直接使用原生类型，尽管如此，我们可能还是会使用typedef来重命名，不过此时只是想使用typedef来缩短类型名字的长度，让使用更加的方便，特别是函数的类型，有时候名字会非常长，如果不缩短名字，用起来非常不方便。
比如：
```c
void (*funp)(int, float, struct student *);
void (*funp1)(int, float, struct student *);
```
每次定义都要写一长串，此时就可以使用typdef。

```c
typedef void (*funType)(int, float, struct student *);
funType p1;
```
		
		
4.6.2 涉及到跨平台
	那么此时就需要typedef定义出新类型名，以面对代码在不同平台的移植。
