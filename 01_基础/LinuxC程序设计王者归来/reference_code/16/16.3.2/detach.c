#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
/* 线程体函数 */
void * tfn1(void * arg)
{
	printf("the thread\n"); /* 输出提示信息 */
	return NULL;
}
int main(void)
{
	int err;
	pthread_t tid;
	pthread_attr_t attr;
	/* 初始化一个线程属性 */
	err = pthread_attr_init(&attr);
	if(err != 0){
		printf("can’t init attr %s\n", strerror(err));
		exit(1);
	}
	/* 将线程属性设置为线程与线程结束状态信息分离 */
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(err != 0){
		printf("can’t set attr %s\n", strerror(err));
		exit(1);
	}
	/* 使用该线程属性创建一个线程，这个线程和其结束状态是分离的 */
	err = pthread_create(&tid, &attr, tfn1, NULL); 
	if(err != 0){
		printf("can’t create thread %s\n", strerror(err));
		exit(1);
	}
	sleep(1);
	/* 由于状态分离，所以不能够得到该线程的结束状态信息，pthread_join函数出错 */
	err = pthread_join(tid, NULL);
	if(err != 0)
		printf("thread has been detached\n");
	return 0;
}
