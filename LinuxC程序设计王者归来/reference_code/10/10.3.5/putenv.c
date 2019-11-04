#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char * p;
	p = getenv("HOME");			 /* 得到环境变量HOME的值 */
	if(p == NULL){
		perror("fail to getenv");
		exit(1);
	}
	printf("$HOME is %s\n", p);	 /* 输出环境变量 */
	if(putenv("HOME=/home/admin") == -1){ /* 修改环境变量HOME的值 */
		perror("fail to putenv");
		exit(1);
	}
	p = getenv("HOME"); /* 再次得到环境变量HOME的值，验证其是否已经修改 */
	if(p == NULL){
		perror("fail to getenv");
		exit(1);
	}
	printf("$HOME is %s \n", p);		/* 输出环境变量 */
	if(putenv("ADMIN=hello") == -1){	/* 添加一个以前没有的环境变量 */
		perror("fail to putenv");
		exit(1);
	}
	p = getenv("ADMIN"); /* 得到环境变量ADMIN的值，验证其是否已经修改 */
	if(p == NULL){
		perror("fail to getenv");
		exit(1);
	}
	printf("$ADMIN is %s \n", p); /* 输出环境变量 */
	return 0;
}
