## 2. c语言的标准IO函数

## 2.1 什么是IO

i（in）：输入
o（out）：输出

从外部设备读取数据就是输入，向外部设备写数据就是输出数据，IO函数就是实现数据输入输出的函数，

有了这些函数后，我们的应用程序只需要调用这些函数即可实现数据的输入输出。

IO函数读写的较为频繁的就是硬盘（外设）上的文件，向文件输出数据就是写数据，从文件输入数据就是读数据。

## 2.2 标准IO与文件IO

### 2.2.1 文件IO

一开始还没有标准IO，只有文件IO，文件IO函数属于OS API，什么是OS API？其实就是操作系统直接提供的系统函数接口。OS会提供很多的API，文件IO函数只是众多API中负责数据输入、输出的API

就算没有标准IO，直接用文件IO一样可以实现数据输入输出，
				
```shell
			 应用程序
					|
					|
			文件IO API 
				 
				 OS 
				 
			 驱动程序
					|
					|
				设 备
(硬盘、键盘、USB、网卡)
```

有关Linux的文件IO函数，我们在“Linux系统编程、网络编程”第一章文件IO中，会进行详细介绍。

### 2.2.2 标准IO

不同OS所提供的OS API不尽相同，尽管有POSIX、BSD等标准来统一的规定OS的接口，要求所有OS应该提供相同的API（应用编程的函数接口），以方便上层编写应用程序的人调用。

事实上不同的OS所提供的接口都有差异，为了屏蔽这种差异，基于文件IO函数（API）的基础又封装了一层库函数，

这就标准IO函数，由c标准库提供，标准IO的“标准”二字，我们可以理解为它提供了更加标准化的“函数接口”。

有了这个标准IO函数后，不管在什么平台上，标准IO函数的用法都是一样的，至于与不同OS的文件IO函数的对接，这件事就由标准io函数来实现，编写应用程序的人无需关心。

标准IO和文件IO的关系图：

```shell
  应用程序
     |
 标准IO函数
     |
 文件IO函数
    OS
```

c标准IO函数的功能和实现细节都是有统一规范的，由ANSI C这个专门制定各种标准的组织来制定。不同的OS都会有自己的文件IO函数，基于不同OS运行的标准IO函数，会封装对接该OS的文件IO函数。

正是由于有标准IO这个玩意，所以我们不论在什么OS上使用printf、scanf函数，函数效果都是一样的，现在几乎所有的OS都支持C标准IO库，所以都能使用标准IO函数。

事实上，标准IO函数除了能够基于OS运行外，实际上也能在裸机（单片机）上运行，总之有了c标准IO函数，只要各个平台都支持，我们不管在什么平台下都可以使用同一套熟悉的标准IO函数。

```shell
		     	 标准IO函数
							 										
Windows   Linux   unix    裸机
```

### 2.2.3 标准IO函数库（标准IO库）

基于OS运行时，标准IO库大多都是动态库，在裸机上运行时标准IO库则是静态库。

“标准IO库”属于“C标准库”的一部分，使用标准IO函数时必须包含stdio.h头文件，因为调用标准IO函数所需的函数声明、相关宏定义、结构体类型定义等等都在stdio.h  

## 2.3 常用c标准IO函数有哪些

对于标准IO函数来说，重点是理解如何使用，而不是死记硬背，忘记时查阅笔记或者百度即可。

### 2.3.1 打开、关闭文件的函数

+ （1）`fopen`：打开文件
+ （2）`fclose`：关闭文件

### 2.3.1 输出函数

+ （1）`fprintf`、`printf`：格式化输出
+ （2）`fputc`、`putc`、`putchar`：输出单个字符
+ （3）`fputs`、`puts`：输出字符串
+ （4）`fwrite`：输出二进制数据

### 2.3.2 输入函数

+ （1）`fscanf`、`scanf`：格式化输入
+ （2）`fgetc`、`getc`、`getchar`：输入单个字符
+ （3）`fgets`、`gets`：输入字符串
+ （4）`fread`：输入二进制数据

### 2.3.3 调整读写位置的函数

+ （1）fseek：调整文件读写指针的位置（调整读写的位置）
+ （2）ftell：返回“文件读写指针”所在位置
+ （3）rewind：将读写位置调整到文件头，从头开始读写

### 2.3.4 fflush：刷新标准IO的库缓存

### 2.3.5 feof：判断是否读到了文件的末尾

## 2.4 标准IO与文件IO的对应关系

基于OS运行的标准io函数，是基于文件io封装得到的。

标准IO函数与文件IO函数的对应关系如下：
不同的OS都有自己的文件IO函数，我们这里是以Linux为例来介绍。


```shell
					打开、关闭文件           输出函数（写）          输入函数（读）           读写定位函数
标准IO： 	fopen  fclose          fprintf、printf         fscanf、scanf              fseek
																fputc、putc、            fgetc、getc、              ftell
																putchar                  getchar                   rewind
																fputs、puts              fgets、gets
																fwrite、perror           fread
                                                                                    
文件IO：	open   close          write                    read                        lseek
```

+ （1）标准IO输出函数和输入函数那么多，但实际上对接的只有个两个函数，read和write所有的输入函数都是基于read封装得到，所有的输出函数都是基于write封装得到。
		`疑问`：文件IO的读写只有read和write函数，但是为什么标准io的输入输出确封装出了一堆的函数？
		 答：方便用户使用，满足各种输入、输出需要。

###（2）feof和fflush是一个纯粹的库函数，不对应任何OS API

## 2.5 常见标准IO函数的用法

### 2.5.1 如何查看标准IO函数的手册

+ （1）在windows下
		我们需要单独下载c标准库手册，里面包含标准IO函数的手册。
		事实上每一个函数在百度百科里面都有详细说明，我们直接查看百度百科也是可以的。

+ （2）Linux自带函数手册（man手册），使用man命令即可查看，除了查看c标准库的函数外，还可以查看Linux OS API
    使用man命令查看c标准库的函数时，需要加数字3，这个在“Linux基础”课程中早就介绍过了。

### 2.5.2 fopen

####（1）函数原型

```c
#include <stdio.h>
FILE *fopen(const char *path, const char *mode);
```

####（2）函数功能

打开文件，供后续进行读写等的操作。

####（3）参数

+ 1）path：为一个字符串，用于指定你要打开文件的“路径名”。
+ 2）mode：也一个字符串，用于指定打开方式
    + （a）r：以只读方式打开文件，此时只能读不能写
				以这种方式打开时，要求文件必须存在，如果不存在，fopen时会返回NULL，表示出错了。

				指定方式："r"

    + （b）r+：以读写方式打开，此时可以读可以写，也要求文件必须存在，否者这就会报错


    + （c）w：以只写方式打开文件
    		+ 如果文件存在，打开成功后，会将文件原有内容全部清空
    		+ 如果文件不存在则会创建这个文件，然后再打开
    
    + （d）w+：以读写方式打开，文件存在的话，打开后将原有内容清空，不存在就创建该文件
    
    
    + （e）a：只写方式打开文件，但是与w不同的是
    		+ 如果文件存在的话，打开成功后，不会清空文件中原有的内容
    			向文件写数据时，会在原有内容的末尾追加数据，a就是add的首字母。
    		
    		+ 不存在就创建该文件

    + （f）a+：以可读可写的追加方式打开文件，如果文件不存在就创建该文件

    + （g）t和b
    		除了以上r、w外，还有b、t，不过b、t是与r/w/a等配合使用的，比如rt/rt+/rb、wt/wb等，如果不明写出b/t的话，默认就为t。
    		
    		+ t：以文本方式打开文件
    		+ b：以二进制方式打开文件
    			在Linux这边并没有这两种打开方式的区别，只有windows才有，而我们的课程方向主要时面对Linux方向，而且b和t区别理解起来很繁琐，就算在windows下，大多数情况下也没有必要区分，因此我们这里不介绍t、b的区别。


#### （4）返回值

+ 1）成功
	返回一个指针 FILE *的指针，我们称为这个“文件指针”，得到这个指针后，就表示文件打开成功了，之后就可以使用这个“文件指针”来读写文件了。

+ 2）失败
	返回NULL，并且errno被设置相应错误的错误号。
	之后我们就可以调用perror或者strerror将错误号翻译为字符串，以提示具体出了什么错误。

#### （5）类型FILE

+ 1）如何查看FILE这个类型
		FILE在stdio.h中，为typedef之后的类型名，

		+ windows下：在IDE的安装目录下可以搜索到stdio.h，比如我可以到Codeblocks IDE的安装目录下找到stdio.h
		+ Linux：Linux系统自带有c标准库的头文件，在/usr/include/目录下，可以找几乎所有的c标准库头文件，其中就包括stdio.h。

+ 2）FILE所对应的原类型
  +（a）windows

			```c
      typedef struct _iobuf FILE; 

			typedef struct _iobuf {
				char *_ptr;     //文件输入的下一个位置
				int   _cnt;     //当前缓冲区的相对位置
				char *_base;    //应该是文件的起始位置
				int   _flag;    //文件标志
				int   _file;    //文件的有效性验证
				int   _charbuf; //标记缓冲的类型
				int   _bufsiz;  //缓存大小
				char *_tmpfname;//临时文件名
			} FILE;
      ```
			
			直接就定义在了stdio.h中，原类型为struct _iobuf。
	 
	 
	+ （b）Linux：

      ```c
      typedef struct _IO_FILE FILE;
      ``` 
			
			原类型为struct _IO_FILE，struct _IO_FILE这个结构体定义在了/usr/include/libio.h中，stdio.h会间接包含libio.h。
			
      ```c
      struct _IO_FILE 
			{
					int _flags;           /* High-order word is _IO_MAGIC; rest is flags. */
					char* _IO_read_ptr;   /* Current read pointer */
					char* _IO_read_end;   /* End of get area. */
					char* _IO_read_base;  /* Start of putback+get area. */
					char* _IO_write_base; /* Start of put area. */
					char* _IO_write_ptr;  /* Current put pointer. */
					char* _IO_write_end;  /* End of put area. */
					char* _IO_buf_base;   /* Start of reserve area. */
					char* _IO_buf_end;    /* End of reserve area. */
					/* The following fields are used to support backing up and undo. */
					char *_IO_save_base; /* Pointer to start of non-current get area. */
												char* _IO_buf_end;    /* End of reserve area. */
					/* The following fields are used to support backing up and undo. */
					...
					...
					int _fileno;  //访问文件描述符用的，这是Linux这边特有的
			};
      ```
			
			
			
	+ （c）FILE是个什么结构体
			打开文件时，这个结构体中放的是标准库函数操作文件的一些基本信息，在后续使用标准IO函数读写文件时需要用到这些基本信息，这也是需事先打开文件的原因，如果不事先打开文件并建立基本信息，后续无法使用标准IO函数来操作文件。
			
			我们这里介绍FILE的结构体原型，只是想让大家知道FILE大概是咋回事，并不是想大家去深究，我们也无法深究，因为我们并不清楚标准io函数源码的具体实现，而且作为应用工程师来说，深究这些没有意义。

	+ （d）为什么windows这边FILE和Linux那边的FILE的原型不一致不一致的原有如下：
			+  只要按照c标准的要求，提供规定功能与格式的标准库io函数即可，至于内部实现完全可以不一样
			
			+  windows与Linux本来就是不同的OS，针对这两个平台的标准IO函数在对接各自的OS时，必然会有所不同
			
			+  针对不同OS的标准库，大多由不同的团队开发，不同的开发团队在实现时，细节必然会有所不同
			
			所以对于标准IO函数来说，只要函数功能、函数格式符合c标准的要求即可，至于代码实现细节不必一样，也不可能完全一样。

#### （6）使用举例

```c
#include <stdio.h>

#define print_error(str) \
do{\
		fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
		perror("error Reason");\
		exit(-1);\
}while(0);

void main()
{
	FILE *fp = NULL;
	
	//fp = fopen("/home/zxf/Desktop/file.txt", "r"); 								//Linux
	fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "r"); //whindows
	if(NULL == fp) print_error("fopen")
	
	printf("%p\n", fp); 

	return 0;
}
```

运行结果为：

```shell
File C:\Users\Administrator\Desktop\EGEProj\qq\a.c, Line 16, Function fopen error
error Reason: No such file or directory
```

以r只读方式打开文件时，文件必须存在，如果不存在就返回NULL，并设置errno报错。

#### （7）fopen如何对接open（文件IO函数）				
我们以Linux这边的标准io函数中fopen为例来介绍？
	
```c
FILE *fopen(const char *path， const char *mode)
		| 创建FILE结构体，在FILE结构体中保存标准IO函数操作时所需的基本信息，其中包括open这个文件IO函数所返回的“文件描述符”
		| 
		|  struct _IO_FILE {
		|  	...
		|		int _fileno; //存放open返回的“文件描述符”
		|  }
		|
		V
int open(const char *pathname, int flags, mode_t mode);
	  |  open这个文件IO函数打开文件时，会建立文件的管理信息，这些管理信息是后续操作文件的基础。
		|  open成功后会返回“文件描述符”，文件IO的读写函数通过“文件描述符”即可读写文件。
		|
	  OS
		|
		|
		V
   文件
```

访问的过程：

```c
文件指针 ————>FILE结构体de _fileno成员（文件描述符） ————> 操作文件
```

2.6 fclose
2.6.1 函数原型
	 #include <stdio.h>
	 int fclose(FILE *stream);

2.6.2 功能：关闭打开的文件
2.6.3 参数：fopen返回的文件指针
2.6.4 返回值
	成功返回0，失败返回EOF宏（宏值为-1），并且errno被设置。

2.6.4 例子：关闭之前fopen的文件
		fclose(fp);
		
		fclose函数一般很少出错，所以一般不进行出错处理。
		
		就算你不主动使用fclose关闭文件，程序结束时也会自动关闭文件，但是如果程序长时间一直运行，而且不会结
	束的话，但是你又需要关闭某文件时，那么你就需要主动调用fclose来关闭文件了。
	
		关闭文件后，fopen函数所开辟的“FILE结构体空间”就会被释放。


2.7 输出函数
  fprintf、printf、sprintf、fputc、putc，putchar，fputs、puts、perror。

2.7.1 fprintf
（1）fprintf
		1）函数原型
			#include <stdio.h>	
			int fprintf(FILE *stream, const char *format, ...);
			
			
			
										 int printf(const char *format, ...);
										 
		2） 功能
			向“文件指针stream”所指向的目标中，格式化输出数据。
			与printf函数相比，这个函数除多了stream参数外，后面的format、...与printf函数一模一样的。
			
		3） 参数
			（a）stream：文件指针，指向了输出目标
			（b）format：“可变参数”的格式
			（c）...：可变参数
				
				比如：fprintf(fp, "score：%f, age：%d", 98.5, 20);
				
				函数会将98.5和20转为字符串"98.5"和"20"，然后将字符串"name：98.5, age：20"写入fp指向的目标（文件）。
				
	4） 返回值
		（a）成功，返回成功输出的字符个数
		（b）失败返回一个负数，具体返回什么负数，手册中并没有强调
				
			
	5）使用举例
		#include <stdio.h>

		#define print_error(str) \
		do{\
						fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
						perror("error Reason");\
						exit(-1);\
		}while(0);

		void main(void)
		{
				FILE *fp = NULL;

				//fp = fopen("/home/zxf/Desktop/file.txt", "w"); 								//Linux
				fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w"); //whindows
				if(NULL == fp) print_error("fopen");

				int ret = fprintf(fp, "score:%f, age:%d", 98.5, 25);
				if(ret < 0) print_error("fprintf");
				
				//fprintf(stdout, "score:%f, age:%d", 98.5, 25);
				
				fclose(fp);

				return 0;
		}

	6） 再说说fprintf的第一个参数stream
			int fprintf(FILE *stream, const char *format, ...);
	
			fprintf第一个参数指向了输出目标，stream可以设置的值有如下三种情况：
			stdout/stderr/fp。
		
		（a）stdout：标准输出
				默认指向了显示器或者打印设备，向显示器、打印设备输出正常信息时，就使用stdout。
				stdout所指向的输出目标为显示器或者打印设备。
				
				疑问：stdout定义在了哪里呢？
				答：这个玩意定义在了stdio.h中，是现成的，可以直接用，同样的stderr也定义在了stdio.h。
				
				当fprintf的第一个参数为stdout时，此时功能与printf完全一样。
				
				
		（b）stderr：标准出错输出
				默认也指向了显示器或者打印设备，专门打印各种报错信息时，就是用stderr。
				
				stderr指向的目标也为显示器或者打印设备。
				
				
				print_error中使用的fprintf，就是用来打印函数出错信息的，所以我们才写为了stderr
				#define print_error(str) \
				do{\
								fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
								perror("error Reason");\
								exit(-1);\
				}while(0);
				
				
				stderr与stdout的区别：
				按照c标准的规定，它们的之前区别如下：
				· stdout
					使用stdout输出数据时，数据会缓冲（积压），当不满足刷新条件时，数据会积压在缓存中而不会被立即
				输出显示。
				
				· stderr
					使用stderr输出时不会缓冲（积压）数据，只要有一个字符的数据就会被立即输出显示，对于报错信息来
				说，错误信息非常的紧急，不能被积压，需要被立即输出，然后告诉“程序员”除了什么出错。

				
		（c）fopen返回的文件指针，指向被打开的文件

		
		
2.7.2 printf
		fprintf(stdout, fmat, ...)可以将数据输出到显示器显示，由于向显示器输出的操作实在是太频繁，而fprintf
	有三个参数，太麻烦，然后就有了printf这个更方便的写法，printf默认就是stdout输出的。
	
		printf其实就是fprintf(stdout, fmat, ...)的简化形式。
	
	
	
	
		
2.7.3 补充：sprintf
	我们再补充一个sprintf，这个函数很有作用，会给我们带来不少的便利。
	
	#include <stdio.h>
	int sprintf(char *str, const char *format, ...);

	它与fprintf唯一不同的只是第一个参数，sprintf的第一个参数也用于指向输出目标，只不过这个输出目标是一个
字符串数组。
	当我们想将整形、浮点数等组合为一串字符串并存放到字符串数组中时，这个函数就能帮到大忙，比如：
	char buf[100] = {};
	
	char name[] = "zhangsan";
	float score = 60.5;
	int age 		= 25;

	sprintf(buf, "people inormation: %s %f %d", name, score, age);
  fprintf(stdout, "%s\n", buf); //打印验证
	
	这个函数的输出目标只是一个数组，所以不需要对接什么文件IO函数，如果让大家自己模拟一个my_sprintf函数，
其实也是能写出来的，大家可以思考一下，这么是实现一个my_sprintf。


2.7.4 fputc
（1） fputc
		1）函数原型
			#include <stdio.h>
			int fputc(int c, FILE *stream);
			
		2）功能
			将字符c输出到stream所指向的目标。
	
		3）参数
			1）c：你想输出的字符
			2）stream：文件指针，指向输出目标
				
				疑问：有同学可能会问，为什么第一个参数是int而不是char，原因有很多，我们这里不去纠结这一点。
				
				
		4）返回值
			1）成功：返回输出字符的编码
			2）失败：返回EOF（-1）
				
				EOF宏定义在了stdio.h中，定义形式为#define	EOF	-1。
				前面说过，读文件时读到了文件的末尾，或者函数出错时就会返回EOF。
				
		5）例子
			fputc('a', stdout);
			fputc('a', stderr);
			fputc('a', fp);
			
2.7.5 putc
		函数原型：int putc(int c, FILE *stream)
		
		功能上是完全等价于fputc，虽然有点细微区别，但是我们不关心这点细微区别，实际上只要使用fputc就可以了。
		
		
2.7.6 putchar
	int putchar(int c);
	等价于putc(c, stdout)和fputc(c, stdout)，为这两个的简化版。
	
	putchar('a');
	
2.7.7 fputs
		专门用于输出字符串，输出字符串时，你可以使用前面fprintf和printf这两个格式化函数，也可以使用这个输出
	字符串的函数。

（1）函数原型
		#include <stdio.h>
    int fputs(const char *s, FILE *stream);

（2）参数
		1）s：指向了要输出的字符串
		2）stream：输出目标
			
（3）返回值
		1）成功：返回输出的字符个数
		2）失败：返回EOF
	
（4）例子
		fputs("hello\n", stdout);
		fputs("hello\n", stderr);
		fputs("hello\n", fp);

2.7.8 puts
	int puts(const char *s);
	
		puts()为fputs(const char *s, stdout)的简写形式，只不过puts会自动帮我们加\n（换行符），所以使用
	puts输出时，我们自己可以不用加换行符，比如：
		puts("hello"); //会自动加上\n来换行

	
2.7.9 fwrite
	前面所介绍的”标准io输出函数”输出的都是字符串(文字编码)，文字编码最后都可以被识别并转换为图形，
供人识别。但是实际上我们也可以将纯二进制数据输出到文件中。
	不过由于文本文件只能识别“文字编码”，不能识别纯二进制数据，因此打开后会显示乱码。
	
（1）函数原型
		#include <stdio.h>
		size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

（2）功能
		访问ptr所指向的nmemb块size大小的连续内存空间中的内容，输出到stream所指向的目标。

			
（3）参数
		1）ptr：空间首字节地址，为什么要加const，在前面的课程中已经解释的非常清楚
		2）size：每块空间的大小
		3）nmemb：块数
		4）stream：输出目标
		
		使用fwrtie向文件写数据时，有两种方式：
		1）将整个空间当做1块来传输
			此时size为这块空间的大小，nmemb为1。
			fwrite(ptr, size, 1, stream);
			
			
		2）将整个空间平均分成多块相同大小的空间，然后输出
			此时size为每个小块的大小，nmemb为块数。
			fwrite(ptr, size, 6, stream);

			我们一会直接看例子。
	
（4）返回值
		成功时，会返回成功写入块数。
		1）函数所有块如果都写成功了的话，返回就应该等于nmemb，说明每一块都写成功了。
		2）如果某几块数据写失败了，返回值<=nmemb，如果返回0的话，就说明一块都没有写入成功

		
（5）例子
		#include <stdio.h>

		#define print_error(str) \
		do{\
				fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
				perror("error Reason");\
				exit(-1);\
		}while(0);

		struct Student
		{
				char name[30];
				float score;
				int age;
				int height;
		}stu[3] = {{"zhangsan", 98.5, 25, 172}, {"lisi", 60.0, 22, 180}, {"王五", 70.5, 27, 175}}; //结构体数组

		void main()
		{
				FILE *fp = NULL;

				//fp = fopen("/home/zxf/Desktop/file.txt", "w"); 						//Linux
				fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w"); //whindows
				if(NULL == fp) print_error("fopen")
				
				/* 格式化输出 */
				int i = 0;
				for(i=0; i<3; i++)
				{	
					fprintf(fp, "%s %f %d %d\n", stu[i].name, stu[i].score, stu[i].age, stu[i].height);
				}	
				
				/* 整块写 */
				int ret = fwrite((void *)&stu, sizeof(stu), 1, fp);
				printf("ret = %d\n", ret);

				/* 分三块写（也就是分三个元素来写） */
				ret = fwrite((void *)&stu, sizeof(struct Student), 3, fp);
				printf("ret = %d\n", ret);
			
				return 0;
		}
		
		打印结果：
			ret = 1
			ret = 3
			
		输入文件的内容：
			文件中的内容：
			zhangsan 98.500000 25 172
			lisi 60.000000 22 180
			王五 70.500000 27 175
			zhangsan            臖   ?   lisi            pB   ?   王五           岯   ?   
			zhangsan            臖   ?   lisi            pB   ?   王五           岯   ?   
			
			只有字符（文字编码）能被正常显示。
		
		
		提问：如果写的是一个整形变量中整数，应该怎么写fwrite。
		很简答，比如
		int a = 10;
		
		fwrite((void *)&a, szief(int), 1, fp);
		
		
（6）为什么要在fwrite中指定size和nmemb

		1）回顾如何访问一片连续的空间
				我们以前讲过，只需要知道两个东西，就能操作一片连续的空间。
				· 空间首字节地址
				· 空间的结束位置
				
		（a）字符串（文字编码数据）
				字符串中的每个字符肯定是紧挨着存放在一片连续空间中的。
				char buf[6] = {"hello"};
				
					hello\0
				
				· 空间首字节地址：字符串的第一个字符所在字节的地址
				· 空间的结束位置：以'\0'字符来判断结尾
				
					操作字符串的存储空间时，只需要传递字符串的“首字符空间的地址”即可，字符串中包含'\0'，操作字
				符串时，会自动通过'\0'来判断结束。
			
				提问：如果字符串的每个字符不是紧挨着的，中间有0（空隙）存在的话，会怎么样？
				答：'\0'的ascii码恰好为0，如果有0存在，字符串就会被截成两段，肯定是不行的。
		
			
		（b）纯二进制数据
				在存放“纯二进制数据”的空间中，中间肯定不可能没有0（空隙），比如
			
			· 数组：
				int buf[] = {1, 2, 3, 4, 5};
				每个元素四个字节，但是每个元素中的数据都很小，一个字节就够了，因此另外三个字节肯定为0，0就是空隙。
				
			· 结构体变量
				在第7章介绍“结构体成员对齐”时就说过，结构体成员之间也会有“空隙”。
				
				由于纯二进制数据中间存在在空隙（0：'\0'），所以不可能通过'\0'来判断结束位置。
			
			如果想要访问存放“二进制数据”的空间的话：
			
			· 首字节地址：空间第一个字节的地址
			
			· 空间的结束位置：通过空间大小来指定，或者通过最后一个字节的地址来指定
				常见的是通过“空间大小”来指定。
							

		2）fwrite中的ptr、size、nmemb参数
			size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
		
			ptr：用于指定空间的第一个字节的地址
			size、nmemb：用于指定空间的大小（size*nmemb），告诉fwrite结束位置
	

2.7.10 perror函数
	  函数原型：
		#include <stdio.h>
    void perror(const char *s);
		
		函数的功能和用法：
		在前面章节已经介绍过，这里不再啰嗦。


2.8 输入函数
	常见输入函数：fscanf、scanf、fgetc、getc、getchar、fgets、gets、fread
	这些输入函数功能，与前面输出函数刚好相反。
	
	
2.8.1 fscanf
（1）函数原型
		#include <stdio.h>
		int fscanf(FILE *stream, const char *format, ...);
		
		
（2）功能
		实现格式化输入。
		从stream指向的目标读取字符串，再根据%d、%f等格式转为整数、浮点数等，然后保存到...的参数中。
		
		与scanf函数相比，除了第一个参数外，其它都是一样的。
			int scanf(const char *format, ...);
		
（2）参数
		1）stream：读取的目标
				stream的设置值有两种：
			（a）stdin：标准输入
						“标准输入”所指向的目标一般都是键盘，所以指定stdin时表示从键盘输入。
						凡事从键盘输入的数据都是“字符（字符编码）”，如果输入10，其实输入的是'1'和'0'的ascii码
					（00110001 00110000），如果你实际想得到的是整形的10（1010），就需要将00110001 00110000转为1010。
				
				
			（b）fp：fopen所返回的文件指针，表示从fp指向的文件中读数据
			
		2）format：指定输入格式，%d、%f、%u、%c等等
		3）...：可变参数 
				不过...中的“可变参数”必须为指针，至于为什么必须为指针，我们在第四章“指针与函数”中就已经讲过了。

（3）返回值
		1）成功：返回读到的数据个数
				int ret = fscanf(stdin, "%d %f %c", &a, &b, &c);
				
			比如上面这个例子，如果三个参数都读到了的话，就返回3，如果只成功读到了两个的话，就返回2。
			
			疑问：什么时候可能会读不到正确的输入？
			答：比如，当不按照“要求的格式”来输入时，就会出现这样的情况。
				
				例子要求输入数据时间隔“空格”，但是如果你间隔的不是“空格”的话，就不会正确的读到数据。
				比如输入时，间隔“逗号”：3,4.5 c
				
				此时，只有12能够被正确的读到，返回值为1。
				
				如果输入时非要间隔"逗号"的话，那么scanf的格式就应该这么写：
				int ret = fscanf(stdin, "%d, %f, %c", &a, &b, &c);
				
				输入格式：3,4.5,c
				
				有关fscanf函数的输入格式五花八门，我们不要去深究，因为这些五花八门的输入格式，都是在“dos系统”
			的那个年代，使用“纯命令行界面”来交互时才会被用到的东西，现在，我们只要能使用fscanf实现基本的输入就
			可以了。
				
		2）如果fscanf函数出错了，又或者读到了文件末尾时，就返回EOF（-1）
		
		
		
（3）例子
		前面已经举过利用stdin来输入的例子，这里直接举从文件输入（读）数据的例子。
		
		例子功能：将结构体成员的数据格式化写入文件，再从文件里面再格式化读出，然后再使用printf打印显示。
			
			#include <stdio.h>

			#define print_error(str) \
			do{\
							fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
							perror("error Reason");\
							exit(-1);\
			}while(0);

			struct Student
			{
					char name[30];
					float score;
					int age;
					int height;
			}stu = {"zhangsan", 98.5, 25, 172}; //结构体数组

			void main()
			{
					FILE *fp = NULL;

					//fp = fopen("/home/zxf/Desktop/file.txt", "w+"); 						//Linux
					fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w+"); //whindows
					if(NULL == fp) print_error("fopen")

					/* 将结构体成员，格式化输出到文件中 */
					fprintf(fp, "%s %f %d %d", stu.name, stu.score, stu.age, stu.height);

					rewind(fp); //将读写的位置调回到文件头

					/* 从文件中读出字符串，格式转换后保存到“结构体变量”的各个成员中 */
					struct Student stu1 = {}; //保存读出的数据
					fscanf(fp, "%s%f%d%d", stu1.name, &stu1.score, &stu1.age, &stu1.height);
					
					//打印读出的数据
					printf("%s %f %d %d", stu1.name, stu1.score, stu1.age, stu1.height);

					fclose(fp);

					return 0;
			}
			
		rewind(fp)的作用：将读写的位置调到文件头，为什么要调到文件头呢？（也就是调整文件最开始的位置）
		因为调用fprintf向文件写完数据后，读写的位置就处在了文件的最末尾处，在文件末尾时是读不到数据的，
	后面还会再介绍rewind函数。
		
		
2.8.2 scanf		
	#include <stdio.h>
	int scanf(const char *format, ...);
	
	对于这个函数我们实在是太熟悉了，这个函数等价于int fscanf(stdin, const char *format, ...)，
是它的简化版，scanf默认就是stdin输入的。

2.8.3 fgetc
（1）原型
		#include <stdio.h>
		int fgetc(FILE *stream);

（2）功能
		与fputc刚好相反，fgetc用来输入字符。
		
		当然，我们完全可以fscanf、scanf来输入字符，但是需要指定的%c格式（比如scanf("%c", &a)），实际上使用
	fgetc来读取“字符”时，使用起来更加的简洁。
		
		
（3）参数 
		stream的设置值：指向要读取的目标
		1）stdin：标准输入，目标指向键盘
		2）fp：fopen返回的文件指针
		
		
（4）返回值
		1）成功：返回读到字符的编码
		2）函数调用失败或者读到了文件的末尾：返回EOF
		
（6）例子
		char ch;
		ch = fgetc(stdin);
		ch = fgetc(fp);
		printf("ch = %c\n", ch);
	
2.8.4 getc	
	int fgetc(FILE *stream);
	int getc(FILE *stream);
	
	完全等价于fgetc，虽然它们之间也有点微小区别，但是我们不需要关心这点微小的区别。

2.8.5 getchar
	#include <stdio.h>
	int getchar(void);

	等价于fgetc(stdin)、以及getc(stdin)。
	ch = getchar(); //默认就是stdin的
	
	getchar是fgetc(stdin)和getc(stdin)的简化形式。
	
	
2.8.5 fgets
（1）原型
		#include <stdio.h>
		char *fgets(char *s, int size, FILE *stream);
		
（2）功能
			从stream所指向的目标，读取字符串到s所指向缓存空间中。
			
（3）参数
		1）s：指向存放“读取到数据”的缓存空间
		2）size：指定要读取的“字符个数”
				size不要大于s指向缓存的大小，否则会导致内存越位，有关什么是内存越位，后面会介绍。
				
				指定size后，实际读取的“字符数”其实为size-1，因为fgets帮我们预留了一个字节自动存放'\0'，
				因为字符串是'\0'结尾的。
				
		3）stream：指向读取目标，设置值为stdin、fp。 
			 
			 
（4）返回值
		1）成功：返回s
		2）失败或者读到了文件末尾：返回NULL
		
		
（5）例子
		1）例子1
			#include <stdio.h>
			
			int main(void)
			{
				char buf[10]; 
				
				fgets(buf, sizeof(buf), stdin);
				printf("%s\n", buf);
				
				return 0;
			}
			
		2)例子2
			#include <stdio.h>

			#define print_error(str) \
			do{\
							fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
							perror("error Reason");\
							exit(-1);\
			}while(0);

			struct Student
			{
					char name[30];
					float score;
					int age;
					int height;
			}stu = {"zhangsan", 98.5, 25, 172}; //结构体数组

			void main()
			{
					FILE *fp = NULL;

					//fp = fopen("/home/zxf/Desktop/file.txt", "w+"); 						//Linux
					fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w+"); //whindows
					if(NULL == fp) print_error("fopen")

					/* 将结构体成员，格式化输出到文件中 */
					fprintf(fp, "%s %f %d %d", stu.name, stu.score, stu.age, stu.height);

					rewind(fp); //将读写的位置调整到文件头

					/* 读取出字符串“zhangsan 98.500000 25 172”，放到buf中 */
					char buf[45] = {0}; //其实就是将每个元素初始化为'\0'
					fgets(buf, sizeof(buf), fp);  //实际读到的字节数为sizeof(buf)-1，最后一个就是之前初始化给的'\0'
					
					puts(buf); //输出显示

					return 0;
			}
			
			输出结果：zhangsan 98.500000 25 172
			
			布置一个作业：大家自己模拟一个myscanf函数，在myscanf函数中调用fgets来从stdin获取字符串，然后按照
			%d、%f等格式的要求，将字符串数据转为整形、浮点等。
				
				
（6）如果内容很多，一次读不完时怎么办
			我们就应该循环的读取，直到读完位置。
			包括fscanf、fgetc等读函数也是一样的，如果一次读不完，就应该循环读取，直到读完位置。
			有关循环读取的例子，我们后面会举例介绍。


2.8.5 gets		
（1）函数介绍
		#include <stdio.h>
		char *gets(char *s);
	
		基本等价于fgets(char *s, int size, stdin);，但是fgets函数存在缺陷。
		
		
（2）gets缺陷：会导致内存越位
			之所以会导致内存越位，是因为这个函数没有size的约束，当输入数据时，不管多少个字符都往数组里面
		存放，就算超过数组的大小时还会一直存放，此时就会越位存放到数组以外的内存空间中。
			
			#include <staio.h>
			
			int main(void)
			{
				char buf[10] = {0};
				gets(buf); 
				
				puts(buf);
			
				return 0;
			}
			
			buf只能放10个字符，当输入字符数量超过10时，就会越位放到数组以外的空间中：
				 buf的空间        非buf的空间
			* * * * * * * * * * x x x x x x 
			0 1 2 3 4 5 6 7 8 9 x x x x x x 
		
			我们介绍这个函数的目的，并不是想让大家使用gets这个函数，由于内存越位的原因，这个函数并不安全，
		所以实际上我们并不建议使用这个函数，介绍gets函数目的只是为了附带介绍什么是“内存越位”。
			
			在以前，黑客往往利用内存越位的漏洞，以内存越位的手段将自己的非法数据比如病毒、木马代码等植入
		到“目标程序”中。
			
			实际上现在OS的安全机制已经非常高了，内存越位的方式将很再难攻击OS。
			
			
（3）其它“内存越位”的例子
		1）例子1
			int buf[7] = {2, 3, 4, 45, 56, 565, 22, 45, 23, 43, 45};	
			
			buf只有7元素空间，结果初始化时给多了值，同样也导致了内存越位。
			
			
		2）例子2
			事实上使用fgets时，如果使用不当的话，也会导致内存越位。
			
			char buf[10]; 
			fgets(buf, sizeof(buf)+30, stdin);
			
			printf("%s\n", buf);
			
			sizeof(buf)+30 > buf的大小，多读取的数据也会导致内存越位，所以指定的size必须<=sizeof(buf)。	
						
		总之，超越合法空间的访问就是内存越位，如果只是越位读的话问题还不大，但是如果是越位写的话，就可能
	会改写其它空间的数据，最后给程序带来严重bug。

			
2.8.6 fread	
（1）函数原型
		#include <stdio.h>
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

（2）功能 
		从stream指向的目标中读取“纯二进制数据”，然后保存到ptr指向的缓存空间。
		
		读取时按块读取，每块的大小为size。
		
		
（3）参数 
		1）ptr：指向存放“读取到数据”的“缓存空间”
		2）nmemb：读取的块数
		3）size：每块的大小
		4）stream：指向要读取的目标
			
（4）返回值 
		1）成功：返回成功读取到的块数。
		2）失败：返回EOF 
				读到文件末尾时也会EOF。
			
（5）例子
			例子功能：使用fwrite将结构体数组以二进制方式写入文件，然后再以二进制方式读出。		
		#include <stdio.h>

		#define print_error(str) \
		do{\
						fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
						perror("error Reason");\
						exit(-1);\
		}while(0);

		struct Student
		{
				char name[30];
				float score;
				int age;
				int height;
		}stu[3] = {{"zhangsan", 98.5, 25, 172}, {"lisi", 60.0, 22, 180}, {"wangwu", 70.5, 27, 175}};//结构体数组

		void main()
		{
				FILE *fp = NULL;

				//fp = fopen("/home/zxf/Desktop/file.txt", "w+"); 						//Linux
				fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w+"); //whindows
				if(NULL == fp) print_error("fopen")


				/* 写 */
				int ret = fwrite((void *)&stu, sizeof(stu), 1, fp);
				printf("ret = %d\n", ret);

				rewind(fp);

				/* 分三块读 */
				struct Student stu1[3] = {0};
				ret = fread((void *)stu1, sizeof(struct Student), 3, fp);
				printf("ret = %d\n", ret);
							
				int i = 0;
				for(i=0; i<3; i++)
				{
						printf("%s %f %d %d\n", stu1[i].name, stu1[i].score, stu1[i].height, stu1[i].age);
				}

				fclose(fp);

				return 0;
		}
		打印结果：
		ret = 1
		ret = 3
		zhangsan 98.500000 172 25
		lisi 60.000000 180 22
		wangwu 70.500000 175 27
		
		如果读一个整形数到int变量中的话，就该这么写：
		int a = 10;
		fread((void *)&a, sizeof(int), 1, fp);


2.9 调整“文件读写指针”的函数
	调整“文件读写指针”，也可以称为调整“文件读写位置”。
	
	涉及的函数：fseek、ftell、rewind。
	
	这里的说法不够准确，实际上只有fseek、rewind会调整文件读写指针，至于ftell的作用，后面再介绍。
	
	
2.9.1 文件读写指针
（1）注意，这里说的是“文件读写指针”，不是“文件指针（FILE *）”，大家千万不要搞混淆了。

（2）简单来说，“文件读写指针”就是读写的“笔尖”，指向了文件中当前访问的位置（字节）。

（3）准确的说说“文件读写指针”到底是个啥
		我们这里说的文件是“普通文件”，“普通文件”都存放在了硬盘上，普通文件的大小就是文件在硬盘上所占据
	存储空间的大小（这句话并不完全准确，目前先这么理解）。
		硬盘也是一个存储器，也是以字节为单位来组成的，每个字节都有自己的地址。
	
		整个文件的大小 =  文件最后一个字节的地址 - 文件首字节地址
		
		“文件读写指针”会记录当前读写的位置在文件中哪一个字节上，那如何记录：
			文件读写指针 = 当前访问字节的地址 - 文件第一个字节地址
			
			“文件读写指针”记录的是当前读写字节与第一个字节的偏移（地址差）。
			
		当访问文件中某个字节时，只要得到该字节的地址即可访问，该字节的绝对地址 = 文件读写指针（偏移） + 文件首字节地址。
		
		大家要区分“文件读写指针”与我们常说的指针，“文件读写指针”只是一个地址差，通过它可以换算出文件中某
	字节的绝对地址。
		
		我们常说的“指针”是一个绝对地址，而且是内存空间的地址。		
		
		
		
（4）刚开始打开文件时，“文件读写指针”是多少
		1）以r/r+/w/w+方式打开文件时
			“文件读写指针”==0，也就说指向了文件的最开始位置，也就是指向了文件的第一个字节。
			从文件的第一个字节开始进行读写操作。
		
		2）以a/a+追加方式打开时
				“文件读写指针”也==0。
				
				在没有任何写操作之前去读的话，就是从第一个字节开始读数据的。
				但是当进行了写操作之后，由于是以追加方式写的，所以“文件读写指针”会被设置为“文件大小”，指向了
			文件的最末尾，数据会被写到文件的末尾，每写一个字节，“文件读写指针”随之向后移动，文件大小也随之
			增加，但是“文件读写指针”一直指向了文件的最末尾。
			
				此时再去读时，读的就是文件的末尾，从文件末尾读什么也读不到，如果想读到数据，就需要将
			“文件读写指针”向前调整，移到我们要读的位置。
				
				
				
2.9.2 fseek
（1）函数原型	
		#include <stdio.h>
    int fseek(FILE *stream, long offset, int whence);

（2）功能
		用来调整“文件读写指针”到我们期望的位置。
		
		
		
（3）参数 
		1）stream：文件指，代表的是普通文件 
		2）whence：粗调，指定值有三个宏，这三个宏被定义在了stdio.h中
			（a）SEEK_SET（宏值1）：调整到文件中首字节
			（b）SEEK_CUR（宏值2）：就停留在当前位置
			（c）SEEK_END（宏值3）：调整到文件最后一个字节					 
						 
							
						 
		3）offset：精调
			（a）负数：从粗调位置向前移动相应字节。
			（b）正数：从粗调位置向后移动相应字节。
			 
			 
			不过需要注意的是：当读写位置已经在文件首字节时，指定负数向前调整是不允许的，
				fseek(fp, -10, SEEK_SET);
				
			之所以不允许，是因为这会访问到其它的空间里面，如果你非要这么设置参数，最后函数会返回-1报错。
			
			如果“文件读写指针”已经指向了文件的最后一个字节，此时再向后调整有意义吗？
				fseek(fp, 100, SEEK_END);
			
			答：有意义，此时会形成空洞文件，有关空洞文件，我们在“Linux系统编程、网络编程”的第1章文件IO中
				有介绍，这里就不啰嗦了。
					
			
（4）返回值
		1）成功，返回0
		2）函数错误，返回-1，并设置errno

		
（5）例子
		1）例子1
			刚开始打开文件时，"文件读写指针"指向了文件首字节，我们尝试向前移动，看看会怎样。
			
			#include <stdio.h>

			#define print_error(str) \
			do{\
					fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
					perror("error Reason");\
					exit(-1);\
			}while(0);

			void main()
			{
					FILE *fp = NULL;

					//fp = fopen("/home/zxf/Desktop/file.txt", "w+"); 						//Linux
					fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w+"); //whindows
					if(NULL == fp) print_error("fopen")

					int ret = 0;

					ret = fseek(fp, -10, SEEK_SET); //*************************
					if(-1 == ret) print_error("fseek")
					
					fclose(fp);

					return 0;
			}
			
			报错：
			File C:\Users\Administrator\Desktop\EGEProj\qq\a.c, Line 34, Function fseek error
			error Reason: Invalid argument
			
			提示无效参数，说明指向首字节时，不能将offset指定负数，在向前调整。
		
		
		2）例子2
				将以前例子中的rewind换成fseek。
				rewind(fp)：将文件读写指针调整到文件首字节
				fseek(fp, 0, SEEK_SET)：一样能将文件读写指针调整到文件首字节
			
				rewind(fp)其实是fseek(fp, 0, SEEK_SET)简化版。
	
	
2.9.3 rewind
	#include <stdio.h>
	void rewind(FILE *stream); 
	
	等价于fseek(stream, 0, SEEK_SET);
	
	其实就是fseek(stream, 0, SEEK_SET)的更方便的简写形式。

	
2.9.3 ftell				
（1）函数原型
		#include <stdio.h>
		long ftell(FILE *stream);		
				
（2）功能	
		返回“文件读写指针”，其实就是返回文件读写写位置距离文件第一个字节的偏移量，也就是返回当前的文件读写位置。
		
		成功：返回文件读写指针（偏移量）。
		
		失败：如果函数出错了就返回-1，errno被设置。

（3）例子
		比如可以使用这个函数得到文件的大小。
		
		fseek(fp, 0, SEEK_END); //将文件指针调整到末尾（最后一个字节）
		int fileSize = ftell(fp);  //返回的就是文件大小

2.9.4 注意：只有普通文件才能调整“文件读写指针”		
		因为只有普通文件在硬盘上有实际的存储空间，调动文件指针才有意义，如果读写的是键盘和显示器的话，
	调整文件杜尔斜指针是没有意义的，比如：
		fseek(stdout, 10, SEEK_END);
		rewind(stdin);
		ftell(stderr);
		都是没有意义的。
		
		因为键盘和显示器只是一个输入、输出设备，stdin和stdout、stderr只是以文件方式来“读写”设备输入输出
	数据而已，并不是一个真正的存储设备（设备），不存在真正的存储空间，调整“文件读写指针”没有意义。
		如果你非要这么做，fseek会报无效参数的错误。
		
		
2.10 检测是否读到了文件的末尾
2.10.1 方法1：通过EOF来检测
		当fscanf、scanf、fgetc等函数读到文件末尾时会返回EOF（-1），我们通过EOF可以检测是否读到了文件的末尾。
	
		但是这种方式有缺点，缺点就是当这些函数出错时，也会返回EOF（-1），所以就不太好判断到底是什么情况
	导致的返回EOF，当然如果非要使用EOF判断的话也是可以的，不过需要加入额外的判断信息，用起来有点繁琐。
	
2.10.2 方法2：通过feof函数来检测。

（1）feof
		1）原型
			#include <stdio.h>
			int feof(FILE *stream);
		
		1）功能：判断是否读到了文件末尾。
		2）stream：指向目标（普通文件）
		3）返回值
			· 读到了文件末尾：返回“非零值”，具体是什么非零值，手册并没有说。
			· 没有读到文件的末尾：返回0
		
				只要检测到返回“非零值”，就说明读到了文件的末尾。
				
				这个函数不存在调用失败的情况，一定会调用成功。

（2）例子			
		功能：file.txt文件中字符很多，一次读不完，所以需要循环读取里面的内容，当检测到读到文件末
			尾时就不再读取。
		
		file.txt内容：
			dsfsffdfdsfsfsdfsfsfsdfsdhfdkljhfgdffkgjkdfsgkdflgjfdkjkdfdklgfdjjjklfjks粉丝哦的放大法
		
		循环读取内容的代码：
		#include <stdio.h>
		
		#define print_error(str) 	\
		do{	\
				fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
				perror("error Reason");	\
				exit(-1);	\
		}while(0);

		void main()
		{
				int ret = 0;
				FILE *fp = NULL;

				//fp = fopen("/home/zxf/Desktop/file.txt", "r"); 									//Linux
				fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "r"); 	//whindows
				if(NULL == fp) print_error("fopen")

				char buf[25] = {0};
				while(1)
				{
						if(feof(fp) != 0)
						{
								printf("文件末尾");
								break;
						}
						fgets(buf, sizeof(buf), fp);
						printf("%s\n", buf);
						memset(buf, 0, sizeof(buf));
				}
				fclose(fp);

				return 0;
		}
		打印结果：
		dsfsffdfdsfsfsdfsfsfsdfs
		dhfdkljhfgdffkgjkdfsgkdf
		lgjfdkjkdfdklgfdjjjklfjk
		s粉丝哦的放大法
		文件末尾
		
		显示打印中文时如果出现乱码的话，可能是因为编码格式问题导致的。
			打印信息是在“命令行”显示的，windows命令行默认支持的中文编码格式为936（GBK：国标）编码，我们可以
		在windows命令窗口输入chcp命令查看：显示结果为936。

		但是如果Codeblocks设置的编码格式不是936的话，那么程序中的中文肯定也不是936编码的，此时我们只需要将
		Codeblocks的编码指定为WINDOWS-936即可，Codeblocks设置方法：
			Setting ——> Editor ——> Encoding setting ——> Use encoding when open files ——> WINDOWS-936
		
		
		
		重新编译运行：
		重新编译时，一定要记得改动下代码再编译（比如加两个空格），如果编译器检测到文件没有任何改动的话，
	编译结果就会还和以前一样，看不到任何效果。
		dsfsffdfdsfsfsdfsfsfsdfs
		dhfdkljhfgdffkgjkdfsgkdf
		lgjfdkjkdfdklgfdjjjklfjk
		s粉丝哦的放大法
		文件末尾
		
		中文字符的编码都是使用2个以上的字节来存放的，所以读取中文字符时，如果不能完整的读出每个汉字的编码的话，
	比如只读取出了某个“汉字”编码的第一个字节，在打印时肯定也会造成乱码，所以读取中文编码时，必须要保证读到
	是每个汉字的完整编码，不能错位，否者打印结果肯定也会乱码。
		
		
		
		
2.11 缓存问题
2.11.1 什么是缓存
	很多同学总是搞不清楚什么是缓存，缓存其实就是程序在内存中开辟的用来存放数据的变量空间，比如：
	int a;
	struct Student stu;
	int *p = malloc(sizeof(int) * 12);  
	float buf[10];
	等等
	
	
		这些变量空间统统都是缓存，自所以称为“缓存”，是因为这个变量空间都是用来暂时存放数据使用的，
	“暂存”就是“缓存”吗。
	
	
2.11.2 应用缓存、库缓存、内核缓存
（1）应用缓存	
		应用代码在内存中开辟的缓存空间。
		
（2）库缓存
		库代码在内存中开辟的缓存空间。
		
（3）内核缓存
		内核代码在内存中开辟的缓存空间。
		不过内核不能使用malloc，因为malloc是一个应用层调用函数，内核里面无法使用这个函数，内核有与之相似
	的函数。
		
		
	很多同学总感觉库缓存和内核缓存很神秘，很难想象长的是什么样子的，实际上库代码、内核代码与应用代码并没
有什么本质区别，就好比中国人和美国人一样，都是人，没有本质区别，应用代码采用了哪些手段来开辟“缓存空间”，
库代码、内核代码同样也是采用这些手段来开辟“缓存空间”的。
	
	一般来说，如果所需的缓存空间很大的话，一般都是使用malloc来开辟的。
		
	
2.11.3 使用标准io读写数据时，数据在缓存中的流向
	应用程序调用标准io函数向底层文件读写数据时，数据并不会直接就写到了文件中，又或者直接就从文件中读到了
数据，而是需要在各个缓存之间进行“捣腾”。
	
	我们这里假设“标准IO”基于OS运行：
																应用代码（应用缓存）
                                	 |	      |
																	 |        |
																标准IO库（标准IO的库缓存）
 															     |        |
																	 |        |
															     OS   （内核缓存）
																   |        |
																	 |        |
														     文件  （硬盘、键盘、显示器）
			
	（1）读数据时
			1）内核函数通过“设备驱动代码”，将数据从文件中读到“内核缓存”空间
			
			2）标准io库调用“读文件IO函数（读API）”，将数据从内核缓存读到“标准IO的库缓存”空间
			
			3）自己写的“应用代码”，调用标准io的读函数，将数据从“标准IO的库缓存”读到“应用缓存”空间，
					数据存放到“应用缓存”空间后，我们的“应用代码”就可以使用读到的数据了。
	
	（2）写数据时
				刚好是读过程的相反过程。
			
			1）“应用代码”调用标准IO库的“写函数”，将数据从“应用缓存”写到“标准IO的库缓存”

			2）标准io库调用“写文件IO函数（写API）”，将数据从“标准IO的库缓存”写到“内核缓存”
			
			3）内核函数通过“设备驱动代码”，将数据从“内核缓存”将数据交给设备。
				显示器设备：显示数据
				硬盘：将数据存入硬盘上的普通文件。
		
	
2.11.4 库缓存的三种缓冲方式
	这里说的“缓冲”就是“积压”的意思，也就是数据会暂时积压在“库缓存”中。
	
	顺便一提，标准io库的库缓存一般为4096大小。
	
	
（1）为什么要积压
		比如以输出为例，如果库缓存中只要有一个字符的数据，就立即调用“文件IO函数（比如write）”将数据输
	出的话，会频繁的调用write函数，这样会降低效率，所以数据会在缓存中先积压，直到满足相关刷新条件时，
	才一次的全部输出。
		
		疑问：什么是刷新？
		答：就将数据从库缓存中取走。
		
（2）三种缓冲方式

			无缓冲、行缓冲、全缓冲。

		1）无缓冲
				无缓冲就是，只要库缓存中有了数据就立即刷新，哪怕只有一个字符，也会立即刷新，数据是不会积压的。
				无缓冲非常适合用于输出错误信息，因为出错信息很紧急，不能被积压，所以有了错误信息后就应该被立
				即无条件刷新输出。
				
				stderr（标准出错输出）就是专门用来输出错误信息的，所以就是“无缓冲”的情况。
				
				不过“无缓冲”的特点是，只要库缓存中有数据了就会立即刷新输出，效率相对会低一些，但是可以将数据
			及时的输出。这就跟送快递的一样，只要有了一个快递就立马送出，如此的话效率肯定会低一些，但是可以
			保证每一个快递都能被及时的送出，一般来说快递都会积压，当挤压到了一定量后再送出，这样的话效率会
			高很多。
					
					
		2）行缓冲
				数据会积压，直到“满一行”时才会刷新，然后将数据输入/输出。
				\n就是一行的判断条件，只要数据中有\n，就代表数据满一行了。
				也就是说，对于标准IO库的库缓存来说，\n不仅仅只是换行，还是数据满一行的标志。
				
				行缓冲非常适合用于正常的键盘输入和打印显示（正常的人机交互），人与计算机的交互就跟人与人的
			说话一样，一句一句的来是最方便的，这样既不会因为说话太急而累到，也不会出现等很久都得不到信息
			的情况。
				
				人机交互时一行其实就是一句，stdin、stdout（标准输入、标准输出）就是专门用来进行正常人机交互用的，
			所以都是行缓冲的，满足一行的条件时就会立即刷输入、输出数据。
	
	
			有关“行缓冲”的需要注意的地方：
				按照c标准的规定，stderr为无缓冲，stdin、stdout为行缓冲，但是针对不同平台的“标准io库”在实现时，
			不一定都会严格的准守c标准，比如：
			· 在Linux下：stderr为“无缓冲”、stdin、stdout为“行缓冲”，准守了c标准的规定
			· 在Windows下：stderr、stdin、stdout都是无缓冲，只要库缓存有数据就会立即刷新。
				
				
		3）全缓冲
				特点是必须等到“库缓存”的空间，全部被数据积压满后，才会输出。
				就好比说以一盆水满了以后才会溢出，道理有点类似。
				
				读写硬盘上普通文件时就是“全缓冲”，比如以写为例，写普通文件时由于不涉及人机交互时的“及时性”问题，
			所以并不需要立即写到文件中，完全可以先将大量数据积压到缓存中，等填满整个缓存之后再一次性刷新输出。
				
				读写fopen所打开的普通文件时，就是“全缓冲”的。
				
				
（2）三种缓冲的基本刷新方式
		我们以输出为例来介绍，输出时的缓冲是我们经常需要关注的。
		
		1）stderr：无缓存
			只要“库缓存”中有数据就无条件立即刷新输出。
			#include <stdio.h>
			
			void main()
			{
					fprintf(stderr, "hello wolrd"); 
					while(1);

					return 0;
			}
			hello wolrd被立即输出。
			
		2）stdout：行缓存
			#include <stdio.h>
			
			void main()
			{
					fprintf(stdout, "hello wolrd");
					fprintf(stdout, "@@@@@@@@@@@");
					printf("22222222222");
					fprintf(stdout, "！！！！！！！！");
					
					while(1); //死循环

					return 0;
			}
			打印结果：无
			
			由于没有\n，所以数据全部被积压在库缓存中，所以看不到打印结果。
			当然如果你的数据够多，躲到能够将整个库缓存填满的话，也会刷新，但是通过stdout输出时，一般输出的
		数据量都很小，不可能将4096大小的缓存空间全部填满。
			
			加\n刷新：
			在最后一个fprintf加\n，会一次性的将所有积压的数据全部被刷新输出，结果为：
			hello wolrd@@@@@@@@@@@22222222222！！！！！！！！
			
			如果给每一个都加上\n的话，每一个都会被立即刷新输出。
			
			
			例子中使用fprintf和printf输出时，全部都是字符串常量，此时的“应用缓存”是什么？
			答：字符串常量放在了.rodata中，所以“应用缓存”空间，就是字符串常量在.rodata中存放时所占用的
				内存空间。
			
			
		3）全缓冲
			#include <stdio.h>
			
			void main()
			{
					FILE *fp = NULL;

					//fp = fopen("/home/zxf/Desktop/file.txt", "w+"); 						//Linux
					fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w+"); //whindows

					fprintf(fp, "hello world\n");

					while(1);

					fclose(fp);

					return 0;
			}
			
				fp指向了普通文件，此时就是全缓存的，尽管"hello world\n"中有个一\n，但是全缓冲不受\n影响，由于
			数据太少，还不足以填满整个库缓存，所以无法被刷新，此时打开file.txt文件时，里面不会有数据。
				
				但是实际上我们向文件里面写数据时，大部分时候写的数据都不多，很难一次性将库缓存全部写满，但是
			我们又必须要刷新数据，然后输出到文件中，此时我们就应该使用其它刷新方式。
		
		
（2）缓冲的其它刷新方式
			无缓冲是无条件立即刷新的，所以不需要什么额外刷新方式，但是行缓冲和全缓冲并不一定会立即刷新，
		当不满足刷新条件时，我们可以使用其它“刷新方式”来刷新？
			
		1）调用fflush刷新函数，手动的刷新库缓存
			 #include <stdio.h>
       int fflush(FILE *stream);
				
			1）例子1 
				void main(void)
				{
					fprintf(stdout, "hello wolrd");
					fprintf(stdout, "@@@@@@@@@@@");
					printf("22222222222");
					fprintf(stdout, "！！！！！！！！");
					fflush(stdout); //手动刷新
					
					while(1); //死循环

					return 0;
				}
				
				Linux下：stderr无缓冲。
				windows：stdout无缓冲。
				
				
			2）例子2
				void main()
				{
						FILE *fp = NULL;

						//fp = fopen("/home/zxf/Desktop/file.txt", "w+"); 								//Linux
						fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w+"); 	//whindows

						fprintf(fp, "hello world\n");

						fflush(fp);
						
						while(1);

						fclose(fp);

						return 0;
				}
			  
				数据被刷新输出到了file.txt中。
			
		2）fclose关闭文件：也会手动刷新
			因为fclose关闭文件时，也会自动的调用fflush函数来手动刷新。
			
			前面我们介绍过，如果没有明写出fclose的话，程序正常终止时，也会自动的调用fclose函数。
			
			比如：
			例子1：
				void main(void)
				{
					fprintf(stdout, "hello wolrd");
					fprintf(stdout, "@@@@@@@@@@@");
					printf("22222222222");
					fprintf(stdout, "！！！！！！！！");
					
					return 0;
				}
				
				程序正常终止时，会默认调用fclose将stdout关闭。
			
			例子2：
			#include <stdio.h>
			
			void main()
			{
					FILE *fp = NULL;

					//fp = fopen("/home/zxf/Desktop/file.txt", "w+"); 						//Linux
					fp = fopen("C:\\Users\\Administrator\\Desktop\\file.txt", "w+"); //whindows

					fprintf(fp, "hello world\n");
					
					
					return 0;
			}
			
			程序结束后，默认会调用flcose关闭fp指向的文件，然后手动刷新输出到文件中。

				
				
				
				
2.12 使用scanf等读取函数，从键盘读取数据时存在的问题				
		从键盘输入数据时，不管输入什么数据，只有当敲了回车（\n）后才会输入，从键盘输入数据时，输入的最后
	输入的字符一定是'\n'。
		
		但是scanf等读取函数从“库缓存”里面读取数据时，往往会将\n留在“库缓存”里面，如果后续紧跟着
	scanf/fscanf/getc/getchar等函数来读取数时，读取到的将是“库缓存”中遗留的'\n'，或者其它无用字符。
	
		比如：
				#include <stdio.h>

				int main()
				{
						char a;
						int b;
						char buf[10];

						char c;

						/* 一下三种不管是那种情况，都会留一个\n在缓存中，影响
						 * 最后一次的‘字符输出’
						*/
						//scanf("%c", &a);
						a = getchar();
						//scanf("%d", &b);
						//scanf("%s", buf);
					
						/* 读到的是来及字符 */
						gets(buf);
						puts(buf);

					 //scanf("%c", &c); //使用getc/getchar也是一样的
					 //printf("%d\n", c);  //会将'\n'的ascii值10输出

						return 0;
				}

		
		注意：以%d、%f格式输入时，输入的必须是0~9的数字，如果是a、b、c、d的英文字母的话，会直接将这些字符
		遗留在库缓存中，影响后续的读取。
		
		
		如何解决：
			很简单，只要将“库缓存”中所有的字符全部取走，将“库缓存”全部清空后，就不会受到这些遗留字符的干扰，
			不管使用getchar、getc、scanf("%c", &ch)中那个函数，都能将遗留的字符全部取走，我们这里使用最简洁
			getchar来实现。
			
			但是由于“库缓存”里面可能一次会遗留很多的字符，所以我们最好是通过一个while循环去读取，由于\n是键盘
		输入的最后一个字符，所以我们以'\n'作为循环结束的条件，当然'\n'也会被取走。
			
				while(getchar() != '\n');  
			 
		表示会将所有的碍眼字符的都取走，当遇到'\n'时结束读取，当然'\n'也会被取走。
		以上代码改进后就变为了如下形式：
				scanf("%c", &a);
				//scanf("%d", &b);
				//scanf("%s", buf);

				while(getchar() != '\n');
				scanf("%c", &c); //使用getc/getchar也是一样的
				printf("%c\n", c);
				
				
		使用scanf、fscanf、getchar、getc、fgetc这些函数时，往往会遗留垃圾字符在库缓存里面，此时我们需要
		使用while(getchar() != '\n')来清库缓存。
				
		不过fgets、gets取数据时不存在遗留垃圾字符的问题，所以到底加不加while(getchar() != '\n')，其实不是好
	判断，最简单的处理方法就是，当你遇到了受到垃圾字符影响的情况时，就加while(getchar() != '\n')来解决，
	没有遇到时就不加清缓存的这句话。
		
		在实际开发产品时，真正使用scanf等来输入的情况非常少，所以基本不会遇到遗留垃圾字符的情况，但是在学
	习c时，scanf等输入函数用的确很频繁，有时可能会遇到，遇到后就按照以上方法来处理。