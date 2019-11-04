#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
int main(void)
{
	pid_t pid;
	struct rusage rusage;
	pid = fork();					/* 创建子进程 */
	if(pid < 0){
		printf("fail to fork\n");
		exit(0);
	}else if(pid == 0){				/* 创建子进程 */
		printf("the child\n");		/* 输出提示信息 */
		exit(0);
	}else
		printf("the parent\n");		/* 输出提示信息 */
	if(wait3(NULL, 0, &rusage) == -1){ /* 等待子进程结束，并且得到该进程的详细信息 */
		perror("fail to wait");
		exit(1);
	}
	printf("utime is %d\n", rusage.ru_utime);	/* 打印用户CPU时间 */
	printf("stime is %d\n", rusage.ru_stime);	/* 打印系统CPU时间 */
	printf("maxrss is %ld\n", rusage.ru_maxrss);	/* 打印最大rss数量 */
	printf("ixrss is %ld\n", rusage.ru_ixrss); /* 打印与其他进程共用代码段的数目 */
	printf("idrss is %ld\n", rusage.ru_idrss);	/* 打印数据段大小 */
	printf("isrss is %ld\n", rusage.ru_isrss);	/* 打印栈大小 */
	printf("minflt is %ld\n", rusage.ru_minflt);	/* 打印软页面错误 */
	printf("majflt is %ld\n", rusage.ru_majflt);	/* 打印硬页面错误 */
	printf("nswap is %ld\n", rusage.ru_nswap);	/* 打印换页次数 */
	printf("inblock is %ld\n", rusage.ru_inblock);/* 打印从文件系统读次数 */
	printf("oublock is %ld\n", rusage.ru_oublock);/* 打印向文件系统写次数 */
	printf("msgsnd is %ld\n", rusage.ru_msgsnd);	/* 打印发送消息数 */
	printf("msgrcv is %ld\n", rusage.ru_msgrcv);		/* 打印接受消息数 */
	printf("nsignals is %ld\n", rusage.ru_nsignals);	/* 打印收到信号数 */
	printf("nvcsw is %ld\n", rusage.ru_nvcsw);		/* 打印主动换页次数 */
	printf("nivcsw is %ld\n", rusage.ru_nivcsw);		/* 打印被动换页次数 */
	return 0;
}
