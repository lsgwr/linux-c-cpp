#include <stdio.h>
int add(int a,int b);
int mul(int a,int b);
int main(void)
{
	int res1,res2;
	res1=add(1,2);
	res2=mul(1,2);
	printf("add:%d,mul:%d",res1,res2);
	return 0;
}
