#include <stdio.h>
int func(int n)
{
  int sum=0,i;
  for(i=1; i<=n; i++)	/* 循环计算每一个整数的和 */
       sum+=i;
  return sum;			/* 返回结果 */
}
int main(void)
{
	int i;
	long result = 0;
	for(i=1; i<=100; i++)						/* 计算1至100的和 */
		result += i;
	printf("result[1-100] = %ld \n", result );	/* 输出结果 */
	printf("result[1-250] = %d \n", func(250) ); /*调用函数func，并且输出结果*/
	return 0;
}
