#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char * p;
	p = getenv("HOME");			  /* 得到环境变量HOME的值 */
	if(p == NULL){				  /* 得到环境变量失败 */
		perror("fail to get env");
		exit(1);
	}
	printf("$HOME is %s\n", p);	  /* 输出环境变量 */
	return 0;
}
