# 6. 指针变量、数组、字符串与sizeof		

## 6.1 sizeof 与 strlen

### 6.1.1 sizeof

sizeof不是函数，sizeof是c语言的关键字，用于获取空间的**字节**(byte)数，参数可以是类型，也可以是变量 
```c
int a;
sizeof(int), sizeof(a)
```
	
### 6.1.2 strlen

strlen是一个字符串函数，用于**统计字符串中字符的个数,不包括'\0'**，参数为字符串指针  

```c
char *p = "hello world";

sizeof(p); //结果为4，为变量p的空间字节数
strlen(p); //11，为字符个数，不包括'\0'
```

	
## 6.2 指针变量与sizeof

```c
int *p;
char *p1;
int (*p2)[10];
int (*p3)[3][4];

sizeof(p)、sizeof(int *);
sizeof(p1)、sizeof(char *);
sizeof(p2)、sizeof(int (*)[10]);
sizeof(p3)、sizeof(int (*)[3][4]);
```

不管什么类型的指针变量，指针变量的大小都是相同的宽度，比如4个字节或者8个字节(取决于地址宽度，第一章有讲)
	
## 6.3 数组与sizeof

### 6.3.1 例子1

```c
int buf[10];

sizeof(buf); 
```

`buf此时为数组名，代表的是整个数组`，此时数组是一个大号的变量，所以sizeof的结果为数组这个大号变量的字节数（40字节）  

```c
sizeof(buf[2]); 
```

每个元素就是一个int变量，所以sizeof的结果为4个字节 
	
	
### 6.3.2 例子2 

```c
void fun(int m, int p[]) //p[] 等价于 *p
{
  printf("%d\n", sizeof(p));
}

int main(void)
{	
  int buf[] = {0, 1, 2, 3, 4, 5, 6};

  fun(7, buf); //&buf[0]，int *

  return 0;
}
```

形参中int p[]的本质为`int *p`，所以sizeof的结果为4/8字节 

很多同学总是被`int p[]`的样子所欺骗，总以为是一个数组，所以sizeof的结果为整个数组的大小，实际上是错的  

当然int p[][n]、int p[][m][n]等也是同样的道理，都是一个指针变量，而不是数组  
+ `int p[][n]`：`int (*p)[n]`
+ `int p[][m][n]`：`int (*p)[m][n]`

sizeof(p)所得的也是指针变量的字节数
	
## 6.3 字符串常量与sizeof	

```c
char buf[] = "hello world";
printf("%d\n", sizeof(buf)); //buf代表的是整个字符数组，所以为12，包括'\0'
printf("%d\n", strlen(buf)); //strlen为字符函数，buf为&buf[0]，用于统计字符个数，为11，不包括'\0'
```

```c
char *p = "hello world";

printf("%d\n", sizeof(p)); //p指针变量名，为整个指针变量的的字节数，为4/8	
```

```c
printf("%d\n", sizeof("hello wolrd"));  //12  
```

"hello wolrd"为字符串常量，放在.rodata中的常量空间中，在sizeof时，此时"hello wolrd"代表整个空间，所以sizeof结果为整个常量空间的字节数，为12  

```c
printf("%d\n", strlen("hello wolrd"));  //统计字符串中字符个数，为12，不包括'\0'
```
strlen为字符串函数，需要传递的参数为字符串第0个字符所在元素的指针。进行函数传参时，如果实参直接写的是字符串常量的话，比如 strlen("hello wolrd")，整个字符串常量代表的是第0个字符所在元素空间的指针  

