#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
void sigalrm_handler(int signo)
{
	/* SIGALRM处理函数什么都不做，只是替换掉默认的终结进程的操作 */
}
void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n"); /* 接收SIGUSR1信号，打印接收信息 */
}
/* my_sleep函数，参数为指定的挂起时间 */
unsigned int my_sleep(unsigned int nsec)
{
	void (*p)(int ) = SIG_DFL;
	/* 加载SIGALRM的处理函数，p用来保存原来的信号处理程序的指针 */
	if( (p = signal(SIGALRM, sigalrm_handler)) == SIG_ERR){ 
		perror("can’t set handler for SIGALRM");
		exit(1);
	}
	alarm(nsec);	/* 设置定时器 */
	pause();		/* 挂起程序，等待被定时器唤醒 */
	if(signal(SIGALRM, p) == SIG_ERR){ /* 恢复SIGALRM的处理函数 */
		perror("can’t rescue handler for SIGALRM");
		exit(1);
	}
	return alarm(0); /* 如果被SIGUSR1以外的信号中断，返回定时器的剩余秒数 */
}
int main(void)
{
	struct timeval begintime, endtime; /* 起始时间和终止时间 */
	float elapsed; /* 消耗的时间，使用浮点值 */
	unsigned int rest;
	/* 设置SIGUSR1的信号处理函数，不设置的话SIGUSR1信号不能从pause函数中唤醒进
	程 */
	if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){ 
		perror("can’t set handler for SIGUSR1");
		exit(1);
	}
	printf("the first time\n");			/* 第一次运行，让进程正常被定时器唤醒 */
	printf("before sleeping\n");
	gettimeofday(&begintime, NULL);	/* 进程挂起前的时间 */
	my_sleep(10);						/* 使进程休眠 */
	printf("after sleep\n");
	gettimeofday(&endtime, NULL);		/* 在进程恢复运行后的时间 */
	/* 将两个时间相减，tv_sec是秒，tv_usec是微秒 */
	elapsed = 1000000 * (endtime.tv_sec - begintime.tv_sec) + 
		endtime.tv_usec - begintime.tv_usec; 
	elapsed /= 1000000;
	printf("elapsed time is %f\n", elapsed); /* 打印实际的休眠时间 */
	printf("the second time\n");		/* 第二次运行，让进程被SIGUSR1信号唤醒 										*/
	printf("before sleeping\n");
	gettimeofday(&begintime, NULL);	/* 得到休眠前时间 */
	/* 开始休眠20秒钟，当读者看到验证该程序的复杂过程后就了解休眠20秒钟还是有必要的 
	*  rest中保存定时器剩余的时间，这个值是秒数
	*/
	rest = my_sleep(20);
	printf("after sleeping\n");
	gettimeofday(&endtime, NULL);		/* 得到进程继续开始运行的时间 */
	elapsed = 1000000 * (endtime.tv_sec - begintime.tv_sec) + 
		endtime.tv_usec - begintime.tv_usec; 
	elapsed /= 1000000;
	printf("actual sleeping-time is %f\n", elapsed); /* 打印实际休眠时间 */
	printf("the rest is %u\n", rest);	/* 打印定时器剩余的时间 */
	return 0;
}
