#include <stdio.h> 
int sum(int a){
	
	int i,res=0;
	for(i=0; i<a; i++){ /* 累加1至a的所有整数的和 */
		res+=i;	
	}
	return res; /* 返回结果 */
}
int main(void)
{
	int a = 10;
	int asum = sum(a);				/* 调用函数 */
	printf("asum is %d \n",asum);	/* 输出结果 */
	return 0;
}
