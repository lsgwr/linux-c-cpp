#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* 清理函数，输出提示信息，用于测试本程序 */
void cleanup(void *arg)
{
	printf("No. %d clean-up procdure\n",*((int *)arg));
										/* 根据不同的参数区别调用的函数 */
}
/* 第一个线程，正常退出线程 */
void *tfn1(void *arg)
{
	int a = 1,b=2;
	printf("the first thread \n");
	pthread_cleanup_push(cleanup, &a); /* 安装清理程序，注意两次安装的程序的号
										码不一样 */
	pthread_cleanup_push(cleanup, &b); /* 加载一个线程退出清理函数 */
	return NULL;						/* 线程退出 */
	pthread_cleanup_pop(0); /* 必须和pthread_cleanup_push函数配对 */
	pthread_cleanup_pop(0);
	return NULL;
}
/* 第二个线程，调用pthread_exit函数退出 */
void *tfn2(void *arg)
{
	int a = 1,b=2;
	printf("the second thread \n");
	pthread_cleanup_push(cleanup, &a); /* 加载一个线程退出清理函数 */
	pthread_cleanup_push(cleanup, &b); /* 加载另一个线程退出清理函数 */
	pthread_exit(NULL);					/* 调用pthread_exit函数退出 */
	pthread_cleanup_pop(0);				/* 执行线程清理函数 */
	pthread_cleanup_pop (0);
	return NULL;
}
/* 第三个线程，休眠10秒钟，等待被取消 */
void *tfn3(void *arg)
{
	int a = 1,b=2;
	printf("the third thread \n");
	pthread_cleanup_push(cleanup, &a); /* 加载一个线程退出清理函数 */
	pthread_cleanup_push(cleanup, &b); /* 加载另一个线程退出清理函数 */
	pthread_cleanup_pop(1);				/* 调用一个清理程序，并从栈中删除记录 */
	printf("ready to sleep\n");
	sleep(10);							/* 休眠，等待被取消 */
	pthread_cleanup_pop(0);				/* 执行线程清理函数 */
	return NULL;
}
int main(void)
{
	pthread_t tid1, tid2, tid3, tid4;
	int err;
	err = pthread_create(&tid1, NULL, tfn1, NULL); /* 第一个线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);
	}
	sleep(1);
	err = pthread_join(tid1, NULL); /* 得到线程的退出状态 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);
	}
	err = pthread_create(&tid2, NULL, tfn2, NULL); /* 第二个线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);
	}
	sleep(1);
	err = pthread_join(tid2, NULL);	/* 得到线程的退出状态 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);
	}
	err = pthread_create(&tid3, NULL, tfn3, NULL); /* 第三个线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);
	}
	sleep(1);
	err = pthread_cancel(tid3);			/* 取消第三个线程 */
	if(err != 0){
		printf("can’t cancel thread %d\n", strerror(err));
		exit(1);
	}
	err = pthread_join(tid3, NULL);	/* 得到线程的退出状态 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);
	}
	return 0;
}
