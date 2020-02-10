#include <stdio.h>
#include <stdlib.h>
/* 进程终止处理函数1 */
void f1(void)
{
	printf("the first exit handler\n");
}
/* 进程终止处理函数2 */
void f2(void)
{
	printf("the second exit handler\n");
}
int main(void)
{
	if(atexit(f1) == -1){ /* 设置第一个进程终止处理函数 */
		perror("fail to set exit handler");
		exit(1);
	}
	if(atexit(f1) == -1){ /* 再次设置第一个进程终止处理函数 */
		perror("fail to set exit handler");
		exit(1);
	}
	if(atexit(f2) == -1){ /* 设置第二个进程终止处理函数 */
		perror("fail to set exit handler");
		exit(1);
	}
	return 0;
}
