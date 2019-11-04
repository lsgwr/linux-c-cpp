#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char * p;
	p = getenv("HOME");							  /* 得到环境变量HOME的值 */
	if(p == NULL){
		perror("fail to getenv");
		exit(1);
	}
	printf("$HOME is %s\n", p);					  /* 输出环境变量 */
	if(setenv("HOME", "/home/admin", 0) == -1){  /* 第一次设置环境变量HOME
													的值，不改变原来的值 */
		perror("fail to setenv");
		exit(1);
	}
	p = getenv("HOME"); /* 再次得到环境变量HOME的值，验证其是否已经修改 */
	if(p == NULL){
		perror("fail to getenv");
		exit(1);
	}
	printf("$HOME is %s \n", p);				  /* 输出环境变量 */
	if(setenv("HOME", "/home/admin", 1) == -1){ /* 第二次设置环境变量HOME的
													值，改变原来的值 */
		perror("fail to setenv");
		exit(1);
	}
	p = getenv("HOME"); /* 再次得到环境变量HOME的值，验证其是否已经修改 */
	if(p == NULL){
		perror("fail to getenv");
		exit(1);
	}
	printf("$ HOME is %s \n", p); /* 输出环境变量 */
	return 0;
}
