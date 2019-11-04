#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
/* 线程体，该线程休眠10秒钟 */
void * tfn1(void * arg)
{
	printf("new thread\n");							/* 输出提示信息 */
	sleep(10);										/* 休眠 */
}
int main(void)
{
	pthread_t tid;
	void * res;
	int err;
	err = pthread_create(&tid, NULL, tfn1, NULL);	/* 创建一个线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	sleep(1);
	err = pthread_cancel(tid);						/* 取消新创建的线程 */
	if(err != 0){
		printf("can’t cancel thread %d\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid, &res);					/* 取得线程的退出信息 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);	
	}
	/* 如果线程被取消，则其退出信息的首地址为PTHREAD_CANCELED常量 */
	if(res == PTHREAD_CANCELED)
		printf("thread %u has been canceled\n", (unsigned int)tid);
	else
		printf("error\n");							/* 不应该出现这种情况 */
	return 0;
}
