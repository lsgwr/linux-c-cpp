#include <stdio.h>

/* 加法函数 */
int add(int a, int b)
{ 
	return a + b; 
}

/* 乘法函数 */
int mul(int a, int b)
{
	return a * b; 
}

int main(void)
{
	/* 定义一个函数指针的数组
	* 这个数组名为op，数组共有两个元素，每个元素是一个函数指针
	* 这个函数指针指向一个有一个整型返回值，并且有两个整型参数的函数
	*/
	int (*op[2])(int a,int b);
	
	op[0]=&add;	/* 第一个指向add函数 */
	op[1]=&mul;	/* 第二个指向mul函数 */
	
	printf("%d %d\n",op[0](1,2),op[1](1,2)); /* 引用这两个数组元素，相当于调用
											  两个函数 */
	
	return 0;
}

