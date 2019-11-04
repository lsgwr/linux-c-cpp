#include <stdio.h> 
int sum(int a){
	int i,res=0;
	for(i=0; i<a; i++){	/* 累加和的循环 */
		res+=i;	
	}
	return res;			/* 输出结果 */
}
int main(void)
{
	int a = 10;
	int asum = sum(a);	/* 调用函数，输出结果 */
	printf("asum is %d \n",asum);
 	return 0;
}
