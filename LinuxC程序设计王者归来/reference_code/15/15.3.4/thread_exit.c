#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
/* 第一个线程，线程体函数返回 */
void * tfn1(void * arg)
{
	printf("the first\n");
	return (void *)1;	
}
/* 第二个线程，调用pthread_exit函数退出 */
void * tfn2(void * arg)
{
	printf("the second\n");
	pthread_exit((void *) 3);		
	printf("should not be here\n");
}
/* 第三个线程，休眠5秒钟后退出 */
void *tfn3(void *arg)
{
	printf("the third, sleep 10 secconds\n");
	sleep(5); /* 休眠5秒钟 */
	return NULL;
}
int main(void)
{
	pthread_t tid1, tid2, tid3;
	void * res; /* 指向线程的退出信息指针 */
	int err; 
	/* 第一个线程的操作 */
	err = pthread_create(&tid1, NULL, tfn1, NULL); /* 创建第一个线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid1, &res); /* 得到线程退出信息——tfn1函数的返回值 */
	if(err != 0){
		printf("can't join thread %d\n", strerror(err));
		exit(1);	
	}
	printf("result from thd1: %d\n", (unsigned int)(res)); /* 输出提示信息 */
	/* 第二个线程的操作 */
	err = pthread_create(&tid2, NULL, tfn2, NULL); /* 创建第二个线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid2, &res); /* 得到线程的退出信息——pthread_exit函数
									的参数所设置的值 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);	
	}
	printf("result from thd2: %d\n", (unsigned int)(res));
	/* 第三个线程的操作 */
	err = pthread_create(&tid3, NULL, tfn3, NULL); /* 创建第三个线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);
	}
	err = pthread_join(tid3, NULL); /* 不关心退出信息，只等待第三个线程退出 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);
	}
	printf("the third thread has done\n");
	return 0;
}
