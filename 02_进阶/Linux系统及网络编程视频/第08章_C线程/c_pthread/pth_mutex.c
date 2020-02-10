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


#define SECON_PTH_NUMS 	2  //次线程数量
#define PTHEXIT 	-1	


/* 传递给线程的参数 */
typedef struct pthread_arg 
{
	pthread_t tid;//存放线程tid
	int pthno;//我自己定义的编号
	int fd;//文件描述符
}ptharg;



struct gloable_va
{
	ptharg pth_arg[SECON_PTH_NUMS];//结构体数组,每个元素会被当做参数传递给对应的次线程
	int pth_exit_flg[SECON_PTH_NUMS];//每个元素存放对应编号线程的退出状态
	pthread_attr_t attr;//存放线程新属性
	pthread_mutex_t mutex;//互斥锁
}glbva = {.mutex = PTHREAD_MUTEX_INITIALIZER};

void print_err(char *str, int line, int err_no)
{
	printf("%d, %s:%s", line, str, strerror(err_no));
	exit(-1);
}

/* 线程退出处理函数 */
void pth_exit_deal(void *arg)
{
	pthread_t tid = ((ptharg *)arg)->tid;	

	printf("!!! pthread %lu exit\n", tid);
}

void *pth_fun(void *pth_arg)
{	
	int fd = ((ptharg *)pth_arg)->fd;
	int pthno = ((ptharg *)pth_arg)->pthno;
	pthread_t tid = ((ptharg *)pth_arg)->tid;	

	//pthread_detach(pthread_self());//线程把自己分离出去

	//注册线程退出处理函数
	pthread_cleanup_push(pth_exit_deal, pth_arg);
	
	printf("pthno=%d, pthread_id=%lu\n", pthno, tid);

	while(1)
	{
		pthread_mutex_lock(&glbva.mutex);//加锁
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
		//检测退出状态
		if(glbva.pth_exit_flg[pthno] == PTHEXIT) break;
		pthread_mutex_unlock(&glbva.mutex);//解锁
	}

	
	pthread_cleanup_pop(!0);	
	return NULL;
	pthread_exit((void *)10); 	
}

void signal_fun(int signo)
{
	if(SIGALRM == signo)
	{
		int i = 0;
		for(i=0; i<SECON_PTH_NUMS; i++)
		{
			//pthread_cancel(glbva.pth_arg[i].tid);//取消次线程
			glbva.pth_exit_flg[i] = PTHEXIT;//设置为退出状态
		}
	}
	else if(SIGINT == signo)
	{
		exit(0);
	}
}

void process_exit_deal(void)
{
	/* 销毁线程的属性设置 */
	int ret = 0;
	ret = pthread_attr_destroy(&glbva.attr);
	if(ret != 0) print_err("pthread_attr_destroy fail", __LINE__, ret);
	
	/* 销毁互斥锁 */
	ret = pthread_mutex_destroy(&glbva.mutex);
	if(ret != 0) print_err("pthread_mutex_destroy fail", __LINE__, ret);

	printf("\nprocess exit\n");
}

int main(void)
{
	int fd = 0;
	int i = 0;
	int ret = 0;
	
	//注册进程退出处理函数,exit正常终止进程时弹栈调用
	atexit(process_exit_deal);
		
	//初始化互斥锁
	ret = pthread_mutex_init(&glbva.mutex, NULL);
	if(ret != 0) print_err("pthread_mutex_init fail", __LINE__, ret);	


	//打开文件,供线程操作,所有的线程(函数)可以共享打开的文件描述符
	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_err("open ./file fail", __LINE__, errno);
	
	/* 初始化护attr, 设置一些基本的初始值 */
	ret = pthread_attr_init(&glbva.attr);
	if(ret != 0) print_err("pthread_attr_init fail", __LINE__, ret);
		
	/* 设置分离属性 */
	ret = pthread_attr_setdetachstate(&glbva.attr, PTHREAD_CREATE_DETACHED);
	if(ret != 0) print_err("pthread_attr_setdetachstate fail", __LINE__, ret);

	/* 通过循环创建两个次线程 */
	for(i=0; i<SECON_PTH_NUMS; i++)
	{
		glbva.pth_arg[i].fd = fd;//保存文件描述符
		glbva.pth_arg[i].pthno = i; //我自己给的线程编号
						           //创建好次线程后,讲次线程分离
		ret = pthread_create(&glbva.pth_arg[i].tid, &glbva.attr, pth_fun, (void *)&glbva.pth_arg[i]);	
		if(ret != 0) print_err("pthread_create fail", __LINE__, ret);
	}

	printf("main tid = %lu\n", pthread_self());

	signal(SIGINT, signal_fun);

	/* 定时5秒,时间到后取消次线程 */
	signal(SIGALRM, signal_fun);
	alarm(3);	

	#if 0
	void *retval = NULL;
	for(i=0; i<SECON_PTH_NUMS; i++)
	{
		//阻塞等待此线程结束,回收次线程资源,并通过第二个参数接受返回值
		pthread_join(glbva.pth_arg[i].tid, &retval);
		printf("@@ %ld\n", (long)retval);
	}
	#endif
		

	while(1)
	{
		pthread_mutex_lock(&glbva.mutex);//加锁
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
		pthread_mutex_unlock(&glbva.mutex);//解锁
	}		
	
	return 0;
}

