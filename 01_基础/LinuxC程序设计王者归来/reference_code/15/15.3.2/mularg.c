#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct arg_struct ARG;
/* 参数结构，有三个参数作为成员变量 
* arg1 : 试验用的参数，字符串类型
* arg2 : 试验用的参数，整型
* arg3 : 试验用的参数，浮点型
* 使用typedef将struct arg_struct类型自定义为ARG
*/
struct arg_struct{
	char arg1[10];
	int arg2;
	float arg3;
};
/* 线程体，打印传递的参数 */
void * thfn(void * arg)
{
	ARG * p = (ARG *)arg; 			/* 强制类型转换，将arg转换为指向ARG类型变
									   量的指针 */
	/* 打印三个参数 */
	printf("arg1 is : %s, arg2 is : %d, arg3 is : %f\n", p->arg1, p->arg2, 	p->arg3); 
	return NULL;
}
int main(int argc, char *argv[ ])
{
	pthread_t tid;
	ARG arg; 												/* 参数结构 */
	int err;
	/* 对三个参数赋值，参数结构要在创建线程之前设置好，一旦创建线程，就必须传递参数结构了 */
	strcpy(arg.arg1, argv[1]);
	arg.arg2 = atoi(argv[2]);
	arg.arg3 = atof(argv[3]);
	err = pthread_create(&tid, NULL, thfn, (void *)&arg);	/*创建线程*/
	if(err != 0){
		printf("can’t create thread %s\n", strerror(err));
		exit(1);
	}
	sleep(1);
	return 0;
}
