#include <stdio.h>
#include <stdlib.h>
extern **environ;			/* 环境变量表的指针 */
int main(void)
{
	if(clearenv() == -1){	/* 清除环境变量 */
		perror("fail to clear env");
		exit(1);
	}
	if(environ == NULL)		/* 环境表全部被清空了 */
		printf("done\n");
	return 0;
}
