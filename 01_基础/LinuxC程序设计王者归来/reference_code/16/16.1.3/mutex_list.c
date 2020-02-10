#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_ITEM 3 /* 每次最多取三个任务 */
typedef struct job * Job;
	/* 链表结点结构 */
struct job{
	pthread_t tid; 	/* 线程ID */
	Job next; 	/* 下一个链表结点 */
	int val; 		/* 结点值 */
};
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
void get_job(Job head, Job task, int *count,pthread_t tid)
{
	Job p,q;
	q = head;			/* 参数是任务队列头 */
	p = q->next;			/* 指针p作为q的后继，两个指针共同前进 */
	while(p != NULL){ 		/* 遍历链表，判断每个任务结点 */
		if(tid == p->tid){	/* 找到属于当前线程的任务结点 */
			q->next = p->next;
			p->next = NULL;	/* 将该结点从原始的任务队列中摘下 */
			while(task->next != NULL)
				task=task->next;
			task->next = p;		/* 链入到新的当前线程的任务队列上去 */
			p = q->next;
			(*count)++;		/* 已取任务是递增 */
		}else{
			q = p;
			p = p->next;
		}
	}

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
/* 新线程，用于读链表中的数据 */ 
void * tfn7(void * arg)
{
	
	int count; 					/* 每次取得链表结点数 */
	Job task;	/* 属于当前线程的任务结点的队列头 */
	task = (struct job *)malloc(sizeof(struct job)); /* 设置头结点，该结点不 存储有效信息 */
	task->next = NULL;
	task->val = 0;
	task->tid = -1;
	pthread_t tid;
	tid = pthread_self();		/* 得到当前线程ID，根据此线程ID判断任务是否归属于当前线程 */
	count = 0;
	while(count < MAX_ITEM)
		if(pthread_mutex_trylock(&q_lock) == 0){ /* 将队列加锁 */
			get_job(arg, task, &count,tid);
			pthread_mutex_unlock(&q_lock); /* 遍历链表结束，释放锁 */
		}
	print(task);
	if(free_job(task) == -1)
		exit(1);
	return (void *)0;
}
int main(void)
{
	Job item; /* 任务队列是一个有头结点的链表 */
	pthread_t tid1, tid2;
	int i,err; 
	item = (struct job *)malloc(sizeof(struct job)); /* 设置头结点，该结点不 存储有效信息 */
	item->next = NULL;
	item->val = 0;
	item->tid = -1;
	/* 创建2个线程，这2个线程会根据自己的线程ID取走不同的任务结点 */
	if((err=pthread_create(&tid1, NULL, tfn7, item)) == -1){ /* 创建第1个线程，将	任务队列头作为线程体函数参数 */
		printf("fail to create thread %s\n", strerror(err));
		exit(0);
	}
	if((err=pthread_create(&tid2, NULL, tfn7, item)) == -1){ /* 创建第2个线程，将	任务队列头作为线程体函数参数*/
		printf("fail to create thread %s\n", strerror(err));
		exit(0);	
	}
	printf("===the 1st put===\n"); /* 第一次执行，由主线程将任务结点设置到任务队列中 */
	pthread_mutex_lock(&q_lock); /*锁住任务队列 */
	for(i = 0; i < 2; i++){ /* 共执行两次，每次放入2个结点，一个属于线程1，一个属于线程2 */
		if(insert(item, i, tid1) == -1)
			exit(1);
		if(insert(item, i + 1, tid2) == -1)
			exit(1);
	}
	if(insert(item, 10, tid1) == -1)
		exit(1);
	pthread_mutex_unlock(&q_lock); /* 释放锁，当前任务队列中由5个任务结点，3个属于线程1，2个属于线程2 */
	sleep(5); 
	/* 休眠，保证线程可以取走任务结点，在这里不能使用pthread_join函数
	* 因为队列中只有2个结点属于线程2，未取走3个结点线程是不会退出的
	* 所以pthread_join函数会导致死锁 
	*/
	printf("===the 2nd put===\n"); 	/*第二次输入，目前队列中已经没有任务结点了 */
	pthread_mutex_lock(&q_lock);	/* 再次锁住队列 */
	if(insert(item, 9, tid2) == -1)
		exit(1);
	pthread_mutex_unlock(&q_lock);	/* 释放锁 */
	/* 这个时候可以使用pthred_join函数了 */
	err = pthread_join(tid1, NULL);	/* 得到线程1的退出信息 */
	if(err != 0){
		printf("can’t join thread %s\n", strerror(err));
		exit(1);
	}
	err = pthread_join(tid2, NULL);/* 得到线程2的退出信息 */
	if(err != 0){
		printf("can’t join thread %s\n", strerror(err));
		exit(1);
	}
	printf("main thread done\n"); /* 输出提示信息 */
	if(item->next == NULL)		/* 如果队列中没有任务结点了，则输出提示信息 */
		printf("No job in the queue\n");	
	free(item); 				   /* 释放头结点 */
	return 0;
}

