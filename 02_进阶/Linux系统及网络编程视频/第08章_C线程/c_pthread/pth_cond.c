#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>


#define SECON_PTH_NUMS 	1  //次线程数量

int va = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void print_err(char *str, int line, int err_no)
{
	printf("%d, %s:%s", line, str, strerror(err_no));
	exit(-1);
}

void signal_fun(int signo)
{
	if(SIGINT == signo)
	{
		pthread_cond_destroy(&cond);
		pthread_mutex_destroy(&mutex);
		exit(0);
	}
	else if(SIGQUIT == signo)
	{
		printf("%lu\n", pthread_self());
	}
}

void *pth_fun(void *pth_arg)
{	
	while(1)
	{
		pthread_mutex_lock(&mutex);
		//之所以讲,mutex传递给该函数,是因为害怕休眠后导致所没有解开,
		//使得其他线程不能使用这个互斥锁,把mutex传递给该函数的目的
		//就是希望该函数如果检查cond没有被设置而休眠时,讲Mutex解锁,
		//让其它线程能够使用这个锁
		pthread_cond_wait(&cond, &mutex);
		printf("va = %d\n", va);
		va = 0;
		pthread_mutex_unlock(&mutex);
	}
	
	return NULL;
}


int main(void)
{
	int i = 0;
	int ret = 0;
	pthread_t tid;

	signal(SIGINT, signal_fun);

	//初始化条件变量	
	ret = pthread_cond_init(&cond, NULL);
	if(ret != 0) print_err("pthread_cond_init fail", __LINE__, ret);


	ret = pthread_create(&tid, NULL, pth_fun, NULL);
	if(ret != 0) print_err("pthread_create fail", __LINE__, ret);


	printf("main %lu\n", pthread_self());
	while(1)
	{	
		pthread_mutex_lock(&mutex);
		va = va + 1;
		
		if(va == 5)
		{
			pthread_cond_signal(&cond);
		}	
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}

	return 0;
}

