#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* 测试使用的结构体。里面有两个成员变量 */
struct a{
	int b;
	int c;	
}r3; /* 定义全局变量r3 */
/* 第一个线程使用局部变量存储退出信息结构 */
void * tfn1(void * arg)
{
	struct a r1;
	printf("the first one:\n");	/* 输出提示信息 */
	r1.b = 10;					/* 设置退出信息结构 */
	r1.c = 11;
	return (void *)(&r1);		/* 返回退出信息结构的首地址 */
}
/* 第二个进程使用动态分配内存的方式存储退出信息结构 */
void * tfn2(void * arg)
{
	struct a * r2; 
	printf("the second one:\n");				/* 输出提示信息 */
	r2 =(struct a *) malloc(sizeof(struct a));	/* 使用动态分配的内存 */
	printf("structure at %x\n", (unsigned int)r2);
	r2->b = 10;									/* 设置退出信息 */
	r2->c = 11;
	return (void *)r2;							/* 返回退出结构的首地址 */
}
/* 第三个进程使用全局变量存储退出信息结构 */
void * tfn3(void * arg)
{
	printf("the third one:\n");					/* 输出提示信息 */
	r3.b = 10;									/* 设置退出信息结构 */
	r3.c = 11;
	return (void *)(&r3);						/*返回退出结构的首地址*/
}
/* 第四个进程使用main函数中的局部变量存储退出信息结构 */
void * tfn4(void * arg)
{
	struct a *r4 = (struct a *)arg;
	printf("the fourth one:\n");					/* 输出提示信息 */
	r4->b = 10;									/* 设置退出信息结构 */
	r4->c = 11;
	return (void *)(&r4);						/*返回退出结构的首地址*/
}
int main(void)
{
	pthread_t tid1, tid2, tid3, tid4;
	void * res;
	int err;
	/* 执行第一个线程 */
	err = pthread_create(&tid1, NULL, tfn1, NULL); /* 创建线程 */
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid1, &res); /* 得到线程的结束信息 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);	
	}
	printf("1st result: %d, %d\n", ((struct a *)res)->b, ((struct a *)	res)->c);						 /* 打印退出信息 */
	/* 执行第二个线程 */
	err = pthread_create(&tid2, NULL, tfn2, NULL);
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid2, &res); /* 得到线程的结束信息 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);	
	}
	printf("2nd result: %d, %d\n", ((struct a *)res)->b, ((struct a *)res) 
	->c);							 /* 输出执行结果 */
	free(res);						 /* 释放res所指向的内存区域 */
	/* 执行第三个线程 */
	err = pthread_create(&tid3, NULL, tfn3, NULL);
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid3, &res); /* 得到线程的结束信息 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);	
	}
	printf("3rd result: %d, %d\n", ((struct a *)res)->b, ((struct a *)res) 
	->c);							 /* 输出执行结果 */
	/* 执行第四个线程 */
	err = pthread_create(&tid4, NULL, tfn2, NULL);
	if(err != 0){
		printf("can’t create thread %d\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid4, &res); /* 得到线程的结束信息 */
	if(err != 0){
		printf("can’t join thread %d\n", strerror(err));
		exit(1);	
	}
	printf("4th result: %d, %d\n", ((struct a *)res)->b, ((struct a *)res) 
	->c);							 /* 输出执行结果 */
	return 0;
}
