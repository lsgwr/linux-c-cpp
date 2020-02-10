#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 1024
int main(void)
{
	char buf[MAX];
	if(getcwd(buf, MAX) == NULL){ /*得到进程的工作目录 */
		perror("fail to get pwd");
		exit(1);
	}
	printf("%s\n", buf);
	if(system("cd ./tmp") == -1){ /* 调用system函数执行cd命令 */
		perror("fail to exec");
		exit(1);
	}
	if(getcwd(buf, MAX) == NULL){ /* 再次得到进程的工作目录 */
		perror("fail to get pwd");
		exit(1);
	}
	printf("%s\n", buf); /* 打印后对比两次的当前工作目录 */
	return 0;
}
