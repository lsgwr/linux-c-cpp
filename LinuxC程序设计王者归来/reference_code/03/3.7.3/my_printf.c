#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define MAX 64
/* 将一个short型变量转换为字符串形式成功返回转换后的字符串首地址，失败返回NULL
* i : 需要转换的短整型，最大值为65536，不处理负数的形式
* p : 转换后的字符串的首地址。p代表存储该串的数组空间的起始位置
*/
char * itoa(int i, char *p)
{
	char *q;
	if(p == NULL)
		return NULL;
	p[0] = (i / 10000) + '0'; /* 将整型转换为字符串，整型的最大不会超过65536，
								 且不处理负数 */
	i = i % 10000;
	p[1] = (i / 1000) + '0';
	i = i % 1000;
	p[2] = (i / 100) + '0';
	i = i % 100;
	p[3] = (i / 10) + '0';
	i = i % 10;
	p[4] = i + '0';
	p[5] = '\0';
	/* 下面的操作用于去除多个0，将第一个有效数字作为第一个数字 */
	q = p;
	while(*q!='\0' && *q == '0')/* 找到第一个非0的数字 */
		q++;
	if(*q != '\0')
		strcpy(p, q); /* 将0后面的数字移动到缓冲区的首地址处 */
	return p;
}
/* 自定义的printf函数，这是一个可变参数的函数。第一个参数固定为字符指针型 
* 返回值是实际输出的字符数
*/
int my_printf(const char *format, ...)
{
	va_list ap;
	char c, ch;
	int i;
	char *p;
	char buf[MAX];			/* 保存字符串的缓冲区 */
	int n = 0;				/* 累计输出字符数 */
	va_start(ap, format);	/* 到达可变参数的起始位置 */
	c = *format;
	while(c != '\0'){
		if(c == '%'){
			format++;		/* 使用'%'进行转义，跳过'%'字符，处理后面的转义字符 */
			c = *format;
			switch(c){
			case 'c': 					/* 处理字符 */
				ch = va_arg(ap, int);	/* 取第一个字符参数 */
				putchar(ch);			/* 输出该字符 */
				n++;
				break;
			case 'd':					/* 处理整数（short） */
				i = va_arg(ap, int);	/* 取该整数参数 */
				itoa(i, buf);			/* 将整数转换为字符串 */
				n += strlen(buf);		/* 累计输出字符数 */
				fputs(buf, stdout);		/* 输出该整数的字符串形式 */
				break;
			case 's':					/* 处理字符串 */
				p = va_arg(ap, char *);/* 取下一个指针参数，保存字符串的首地址*/
				n += strlen(p);
				fputs(p, stdout);		/* 输出该字符串 */
			}
		}else{
			putchar(c);					/* 普通字符，则输出该字符 */
			n++;
		}
		format++;						/* 处理下一个字符 */
		c = *format;
	}
	va_end(ap);							/* 做一些清理工作 */
	return n;							/* 返回实际输出的字符数 */
}
int main(void)
{
	/* 调用my_printf函数输出字符、整型和字符串 */
	my_printf("the char is : %c\n, the number is : %d\n, the string is : %s\n", 
	'a', 100, "hello world\n"); 
	return 0;
}

