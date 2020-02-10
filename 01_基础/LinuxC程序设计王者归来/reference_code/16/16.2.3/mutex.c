#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
typedef struct job * Job;
/* 链表结点结构 */
struct job{
	pthread_t tid;	/* 线程ID */
	Job next; 	/* 下一个链表结点 */
	int val; 		/* 结点值 */
};
struct timeval begintime;
pthread_mutex_t q_lock = PTHREAD_MUTEX_INITIALIZER; /* 全局变量锁 */
int insert(Job head, int val, pthread_t tid)
{
	Job p, q;
	p = head; 		/* 头指针 */
	if(p != NULL){	/* 判断空链表的情况 */
		while(p->next != NULL){
			p = p->next;
		}
	}
	q = (Job)malloc(sizeof(struct job)); /* 为结点分配内存空间 */
	if(q == NULL){
		perror("fail to malloc");
		return -1;
	}
	q->next = NULL;
	q->val = val;
	q->tid = tid;	/* 设置结点的所有者，线程1 */
	if(p == NULL){ 	/* 设置链表头指针 */
		head = q;
		return 0;
	}
	p->next = q; 	/* 插入到队列中 */
	return 0;
}
int free_job(Job head)
{
	Job p,q;
	for(p = head; p != NULL; p = p->next){ /* 线程退出时释放所有的任务结点 */
		q = p;
		free(q);
	}
	return 0;
}
void print(Job head)
{
	Job p;
	for(p = head->next; p != NULL; p = p->next) /* 输出取得的任务列表 */
		printf("thread %u: %d\n", (unsigned int)p->tid, p->val);
}
/* 线程体函数 */
void * tf9(void * arg)
{
	long long count; /* 工作数量 */
	Job p,q;
	Job task = NULL;
	task = (struct job *)malloc(sizeof(struct job)); /* 设置头结点，该结点不 存储有效信息 */
	task->next = NULL;
	task->val = 0;
	task->tid = -1;
	pthread_t tid;
	
	struct timeval endtime;
	float elapsed_time;
	tid = pthread_self(); /* 得到线程ID */
	count = 0;
	while(count < 100000000){ /* 循环次数很多 */
		if(pthread_mutex_trylock(&q_lock) == 0){ /* 得到互斥量锁住临界区*/
			q = (Job)arg;
			p = q->next; 
			while(p != NULL){ /* 遍历整个队列 */
				if(tid == p->tid){
					count++; /* 找到一个属于自己的作业结构 */
				}
				p = p->next;
			}
			pthread_mutex_unlock(&q_lock); /* 释放互斥量 */
		}
	}
	gettimeofday(&endtime, NULL); /* 计算运行的时间，得到一个整数表示经过了多少秒 */
	elapsed_time = 1000000 * (endtime.tv_sec-begintime.tv_sec) + endtime.tv_usec - begintime.tv_usec;
	elapsed_time /= 1000000;
	printf("This total used time is: %f seconds.\n", elapsed_time);
	return (void *)0;
}
int main(void)
{
	Job item;
	pthread_t tid1, tid2;
	int i,err;
	gettimeofday(&begintime, NULL); /* 得到程序运行的起始时间 */
	item = (Job)malloc(sizeof(struct job)); /* 初始化链表头 */
	item->next = NULL;
	item->val = 0;
	item->tid = -1;
	if((err=pthread_create(&tid1, NULL, tf9, item)) == -1){ /* 创建第1个线程 */
		printf("fail to create thread %s\n", strerror(err));
		exit(1);
	}
	if((err=pthread_create(&tid2, NULL, tf9, item)) == -1){ /* 创建第2个线程 */
		printf("fail to create thread %s\n", strerror(err));
		exit(1);
	}
	printf("===the 1st put===\n");
	pthread_mutex_lock(&q_lock); /* 得到写锁，进入临界区 */
	for(i = 0; i < 2; i++){ /* 向队列中插入作业结点 */
		if(insert(item, i, tid1) == -1)
			exit(1);
		if(insert(item, i + 1, tid2) == -1)
			exit(1);
	}
	if(insert(item, 10, tid1) == -1) /* 多插入一个作业结构，该结构属于线程1 */
		exit(1);
	pthread_mutex_unlock(&q_lock); /* 释放互斥量 */
	printf("===the 2nd put===\n");
	pthread_mutex_lock(&q_lock); /* 再次得到互斥量，插入一个属于线程2的结点 */
	if(insert(item, 9, tid2) == -1)
		exit(1);
	pthread_mutex_unlock(&q_lock);
	err = pthread_join(tid1, NULL); /* 得到线程1的结束信息 */
	if(err != 0){
		printf("can’t join thread %s\n", strerror(err));
		exit(1);
	}
	pthread_join(tid2, NULL); /* 得到线程2的结束信息 */
	if(err != 0){
		printf("can’t join thread %s\n", strerror(err));
		exit(1);
	}
	printf("main thread done\n");
	return 0;
}

