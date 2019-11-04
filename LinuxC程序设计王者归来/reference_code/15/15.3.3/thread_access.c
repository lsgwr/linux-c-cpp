#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* 参数结构，将一个堆的指针和一个进程局部变量的指针传递给新线程 */
typedef struct arg_struct{
	int * heap;		/* 堆数据的指针 */
	int * stack;	/* 栈数据的指针 */
}ARG;
FILE *fp = NULL;		/* 文件对象指针，里面包括流缓冲区和文件描述符 */
/* 线程体，改变进程的堆数据和栈数据的值 */
void * thfn(void * arg)
{
	ARG * p;
	p = (ARG *)arg;
	(*p->heap)++;	/* 堆数据递增 */
	(*p->stack)++;	/* 栈数据递增 */
	/* 向文件输出更改后堆和栈的值，该文件的流对象是一个全局变量，
	* 试验线程操作全局变量的能力。 
	*/
	fprintf(fp, "new thread heap:%d stack :%d\n", *(p->heap), *(p->stack));
	printf("the new thread done\n");
	return NULL;
}
int main(void)
{
	pthread_t tid, tid2;
 	ARG arg;
	int * heap;
	int stack;
	int err;
	heap = (int *)malloc(1 * sizeof(int)); /* 分配空间，得到堆数据 */
	if(heap == NULL){
		perror("fail to malloc");
		exit(1);
	}
	*heap = 2;
	stack = 3; /* 栈数据初值为3 */
	/* 设置arg参数结构，栈数据必须以指针的形式传递给新线程 
	* 全局变量可以在线程函数体中直接引用
	* 堆数据的操作方式主要看其首地址的指针的存储方式
	*/
	arg.heap = heap;
	arg.stack = &stack;
	if( (fp = fopen("test.txt", "wb")) == NULL){ /* 打开文件 */
		perror("fail to open");
		exit(1);
	}
	err = pthread_create(&tid, NULL, thfn, (void *)&arg); /* 创建线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);
	}
	sleep(10); /* 保证新线程先运行 */
	(*heap)++; /* 主线程也递增堆数据和栈数据 */
	stack++;
	/* 向文件输出信息，该文件和线程的输出文件是同一个文件 */
	fprintf(fp, "main thread: heap:%d stack :%d\n", *(arg.heap), 	*(arg.stack));	
	printf("the main thread done\n");
	fclose(fp); /* 关闭文件 */
	free(heap); /* 释放堆数据 */
	return 0;
}
