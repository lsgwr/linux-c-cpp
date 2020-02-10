/* 包含文件 */
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "iolib.h"		/* 自制的读写I/O库函数 */
/* 全局宏 */
#define MAX_LINE 1024	/* 缓冲区大小 */
/* 调试开关 */
#define BUG 1
/* 调试输出，使用宏实现 */
#ifdef BUG
#define DEBUG_PRINT(str); 	printf(str);
#endif
/* 函数接口声明 */
/* web_server.c */
extern int init(struct sockaddr_in * sin, int * lfd, int * port, char * path);
extern int error_page(int sock_fd);
extern int get_path(int cfd, char * path);
extern int write_page(int cfd,int fd, char * path);
