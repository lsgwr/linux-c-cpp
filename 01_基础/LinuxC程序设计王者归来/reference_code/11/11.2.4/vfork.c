#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int global;								/* 全局变量，数据段内 */
int main(void)
{
	pid_t pid;
	int stack = 1;						/* 局部变量，栈内 */
	int * heap;
	heap = (int *)malloc(sizeof(int));	/* 动态内存分配，堆内 */
	*heap = 2;
	pid = vfork();						/* 调用vfork创建一个进程 */
	if(pid < 0){						/* 创建子进程失败 */
		printf("fail to fork\n");
		exit(1);	
	}else if(pid == 0){					/* 子进程 */
		global++;						/* 修改栈、堆和数据段 */
		stack++;
		(*heap)++;
		printf("data : %d, stack : %d, heap : %d\n", global, stack, *heap);
		printf("child terminates\n"); /* 子进程结束运行 */
		exit(0);						/* 进程正常退出 */
	}
	/* sleep(2); 不再需要休眠以保证子进程先运行 */
	printf("data : %d, stack : %d, heap : %d\n", global, stack, *heap);
	printf("parent terminates\n");
	return 0;
}
