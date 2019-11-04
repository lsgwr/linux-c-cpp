#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int global;								/* 全局变量，在数据段中 */
int main()
{
	pid_t pid;
	int stack = 1;						/* 局部变量，在栈中 */
	int * heap;
	heap = (int *)malloc(sizeof(int));	/* 动态分配的内存，在堆中 */
	*heap = 2;
	pid = fork();						/* 创建一个子进程 */
	if(pid < 0){						/* 创建子进程失败 */
		printf("fail to fork\n");
		exit(1);	
	}else if(pid == 0){					/* 子进程，改变各变量的值 */
		global++;						/* 修改栈、堆和数据段 */
		stack++;
		(*heap)++;
		printf("the child, data : %d, stack : %d, heap : %d\n", global, stack, 
		*heap);
		exit(0);						/* 子进程运行结束 */
	}
	sleep(2);							/* 父进程休眠2秒钟，保证子进程先运行 */
	printf("the parent, data : %d, stack : %d, heap : %d\n", global, stack, 
	*heap);								/* 输出结果 */
	return 0;
}
