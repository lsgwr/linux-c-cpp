#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* 线程函数，打印进程ID和线程ID */
void * thfn(void * arg)
{
	pid_t pid;				/* 进程ID */
	pthread_t tid;			/* 线程ID */
	pid = getpid();			/* 得到进程ID */
	tid = pthread_self();	/* 得到线程ID */
	/* 将两个ID转换为无符号整数打印 */
	printf("the new thread: pid is: %u, tid is: %u\n", (unsigned int)pid, 
	(unsigned int)tid);
	return NULL;
}
int main(void)
{
	pid_t pid;
	int err;
	pthread_t tid, mtid;
	pid = getpid();
	mtid = pthread_self(); 							/* 得到主线程的线程ID */
	err = pthread_create(&tid, NULL, thfn, NULL); /* 创建线程，如果出错
													err保存错误号 */
	/* 错误号和errno一样，可以由strerror函数将编号映射为容易理解的描述性语言 */
	if(err != 0){
		/* 不能使用perror函数，因为错误号不在errno变量内 */
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	/* 休眠一秒钟，保证新创建的线程在主线程之前被调用 */
	sleep(1);
	/* 打印主线程ID和进程ID */
	printf("the main thread: pid is: %u, tid is: %u\n", (unsigned int)pid, 
	(unsigned int)mtid);
	return 0;
}
