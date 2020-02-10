#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
/* 线程体函数 */
void * tfn1(void * arg)
{
	printf("the thread\n"); /* 输出提示信息 */
	sleep(5); /* 休眠5秒钟，等待主线程将该线程设置为分离状态 */
	printf("the thread done\n");
	return NULL;
}
int main(void)
{
	int err;
	pthread_t tid;
	err = pthread_create(&tid, NULL, tfn1, NULL); /* 创建一个线程 */
	if(err != 0){
		printf("can’t create thread %s\n", strerror(err));
		exit(1);
	}
	sleep(1);
	err= pthread_detach(tid); /* 设置线程为分离状态 */
	if(err != 0){
		printf("can’t detach thread %s\n", strerror(err));
		exit(1);
	}
	/* 由于状态分离，所以不能够得到该线程的结束状态信息，pthread_join函数出错 */
	err = pthread_join(tid, NULL);
	if(err != 0)
		printf("thread has been detached\n");
	sleep(5); /* 确保线程执行完毕 */
	printf("the main thread done\n");
	return 0;
}
