#include "common.h"
int main(int argc,char *argv[])
{
	char c1,c2;
	int interval;
	int duration;
	int intervation = 0;
	int reportType = 0;	
	char repTypeName[16];
	struct timeval now;
	reportType = STANDARD; 					/* 该程序默认使用STANDARD版本 */
	strcpy(repTypeName,"Standard");
	if(argc>1){
		sscanf(argv[1],"%c%c",&c1,&c2);	/* 得到该程序的命令行参数 */
		if(c1 != '-'){ /* 命令行参数出错 */
			printf("wrong command]\n");
			exit(1);
		}
		if(c2 == 's'){ /* -s使用SHORT版本 */
			reportType = SHORT;
			strcpy(repTypeName,"Short");
		}else if(c2 == 'l'){ /* -l 使用LONG版本 */
			reportType = LONG;
			strcpy(repTypeName,"Long");
			interval = atoi(argv[2]); /* 得到两个参数，分别是取平均系统负载的时
									间间隔和总时长 */
			duration = atoi(argv[3]);
		}
	}
	gettimeofday(&now,NULL);				/* 得到当前的系统时间 */
	/* 输出版本的类型，standard、short和long */
	printf("Status report:  %s\nat the time of : %s\n", repTypeName,(char *)ctime(&(now.tv_sec))); 
	/* 输出主机名，该信息存储在/proc/sys/kernel/hostname文件中 */
	printf("the hostname is: "); 
	search( "/proc/sys/kernel/hostname" , "" );
	switch(reportType){ 
	case 0: 								/* STANDARD版本 */
		search( "/proc/cpuinfo" , "model name" ); /* CPU的类型和型号 */
		search( "/proc/version" , "" );	/* 所使用的Linux内核的版本 */
		break;
	case 1: 								/* SHORT版本 */
		search( "/proc/stat" , "cpu" ); /* 总共有多少CPU时间执行在用户态、系统态和空闲态 */
		search( "/proc/stat" , "intr" ); /* 磁盘读写请求数 */
		search( "/proc/stat" , "ctxt" ); /* 内核已经进行了多少次进程上下文的切换 */
		search( "/proc/stat" , "btime" ); /*系统最后的启动时间*/
		search( "/proc/stat" , "processes" ); /* 从系统启动以来创建的进程数 */
		break;
	case 2: /* LONG版本 */
		search( "/proc/meminfo" , "MemTotal" ); /* 配置内存的大小 */
		search( "/proc/meminfo" , "MemFree" ); /* 当前可用内存数 */
		while(intervation < duration){ /* 取得平均系统负载 */
			sleep(interval);
			if(get_load_avg() == -1)
				exit(1);
			intervation += interval;
		}
		break;
	default:
		printf("should not be here\n");
	}
	return 0;
}

