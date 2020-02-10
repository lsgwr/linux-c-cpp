#include "common.h"

int main(void)
{
	int a, b, res;
	
	/* 使用四个全局变量的函数指针来引用这四个函数 */
	p1 = add;
	p2 = sub;
	p3 = mul;
	p4 = div;
		
	a = 2; b = 1; /* 两个临时变量 */
	
	res = (*p1)(a, b); /* 和 */
	printf("add : %d\n", res);
	
	res = (*p2)(a, b); /* 差 */
	printf("sub : %d\n", res);
	
	res = (*p3)(a, b); /* 积 */
	printf("mul : %d\n", res);
	
	res = (*p4)(a, b); /* 商 */
	printf("div : %d\n", res);
		
	return 0;
}

