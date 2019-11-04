#include "common.h"
/* 读取系统平均负载的函数，成功返回0，失败返回-1 */
int get_load_avg()
{
	char line_buf[MAX];
	int fd;
	int n;
	int res = -1;
	if((fd = open("/proc/loadavg", O_RDONLY)) == -1){ /* 打开存储系统平均负
														载的porc文件 */
		perror("fail to loadavg");
		return -1;
}
	if((n = read(fd, line_buf, MAX)) == -1){ /* 读取系统平均负载的内容 */
		perror("fail to read");
		goto err;
	}
	line_buf[n] = '\0';
	printf("Average Load: %s", line_buf); /* 输出系统的负载 */
	res = 0;
err:
	close(fd); /* 关闭文件 */
	return res;
}
/* 在指定的proc文件中查找需要的内核信息，成功返回0，失败返回-1。
* path : 指定的proc文件的路径
* name : 所要查找的内核信息
 */
int search(char *path, char *name)
{
	int fd;
	char char_all[MAX] = "\0";
	char line_buf[MAX] = "\0";
	char *p;
	char *s;
	int n;
	int res = -1;
	if((fd = open(path ,O_RDONLY)) == -1){ /* 打开指定的proc文件 */
		perror("fail to open");
		return -1;
	}
	if((n = read(fd, char_all, MAX)) == -1){ /* 将文件内容读入缓冲区 */
		perror("fail to read");
		goto err;
	}
	char_all[n] = '\0';
	p = strstr(char_all, name);	/* 搜索name表示的内核信息，strstr函数查找字符
								  // 串，返回该字符串的地址 */
	s = strstr(p, "\n"); 		/* 这一行就是所需要的内核信息 */
	n = s - p + 1;
	//printf("p=%lld,n=%d,s=%lld\n",p,n,s);
	//printf("%s",name);
	strncpy(line_buf, p, n); 
	printf("%s\n",line_buf);	/* 输出缓冲区的内容 */
	res = 0;
err:
	close(fd);
	return res;
}
