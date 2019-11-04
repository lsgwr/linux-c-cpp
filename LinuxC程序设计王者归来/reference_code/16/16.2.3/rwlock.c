#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
typedef struct job * Job;
/* 链表结点结构 */
struct job{
	pthread_t tid; 	/* 线程ID */
	Job next; 	/* 下一个链表结点 */
	int val; 		/* 结点值 */
};
struct timeval begintime;
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
void * tf10(void * arg)
{
	pthread_rwlock_t q_rwlock;
	long long count; /* count of jobs */
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
	while(count < 100000000){
		if(pthread_rwlock_tryrdlock(&q_rwlock) == 0){ /* 锁住队列，使用的是读锁 */
			q = arg;
			p = q->next; 
			while(p != NULL){ /* 遍历队列，寻找属于该线程的作业结构 */
				if(tid == p->tid){ 
					count++;
				}
					p = p->next;
			}
			pthread_rwlock_unlock(&q_rwlock); /* 释放读锁 */
		}
	}
	gettimeofday(&endtime, NULL); /* 得到线程结束运行的时间 */
	elapsed_time = 1000000 * (endtime.tv_sec-begintime.tv_sec) + endtime.tv_usec -begintime.tv_usec;
	elapsed_time /= 1000000;      	/* 计算执行的时间 */
	printf("This total used time is: %f seconds.\n", elapsed_time);	/* 输出执行时间用于比较 */
	return (void *)0;
}
int main(void)
{
	Job item;
	pthread_t tid1, tid2;
	pthread_rwlock_t q_rwlock;
	int i,err;
	pthread_rwlock_init(&q_rwlock, NULL); /* 初始化读写锁 */
	gettimeofday(&begintime, NULL);         /* 得到程序起始的运行时间 */
	item = (Job)malloc(sizeof(struct job)); /* 初始化链表的头结点 */
	item->next = NULL;
	item->val = 0;
	item->tid = -1;
	if((err=pthread_create(&tid1, NULL, tf10, item)) == -1){ /* 创建第1个线程 
															   */
		printf("fail to create thread %s\n", strerror(err));
		exit(0);	
	}
	if((err=pthread_create(&tid2, NULL, tf10, item)) == -1){ /* 创建第2个线程 
															   */
		printf("fail to create thread %s\n", strerror(err));
		exit(0);	
	}
	printf("===the 1st put===\n");
	pthread_rwlock_wrlock(&q_rwlock); /* 锁住链表，向其中插入五个作业结构，使用
										的是写锁 */
for(i = 0; i < 2; i++){
		if(insert(item, i, tid1) == -1)
			exit(1);
		if(insert(item, i + 1, tid2) == -1)
			exit(1);
	}
	if(insert(item, 10, tid1) == -1) /* 再次插入一个结点 */
		exit(1);
	pthread_rwlock_unlock(&q_rwlock); /* 释放写锁 */
	sleep(1);							/* 休眠一秒钟，等待两个线程运行 */
	printf("===the 2nd put===\n");
	pthread_rwlock_wrlock(&q_rwlock); /* 再次锁住作业结构队列，使用写锁 */
	if(insert(item, 9, tid2) == -1)
		exit(1);
	pthread_rwlock_unlock(&q_rwlock); /* 释放写锁 */
	err = pthread_join(tid1, NULL);	/* 得到线程1的结束信息 */
	if(err != 0){
		printf("can’t join thread %s\n", strerror(err));
		exit(1);
	}
	pthread_join(tid2, NULL);		/* 得到线程2的结束信息 */
	if(err != 0){
		printf("can’t join thread %s\n", strerror(err));
		exit(1);
	}
	printf("main thread done\n");
	pthread_rwlock_destroy(&q_rwlock); /* 销毁读写锁 */
	return 0;
}
