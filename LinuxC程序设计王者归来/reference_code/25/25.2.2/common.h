#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include "iolib.h"		/* 自制的I/O库函数 */
/* 全局宏定义区 */
#define MAX_LINE 1024	/* 向服务器端发送的命令的最大长度 */
#define PORT 8000			/* 端口号 */
#define COMMAND_LINE 256	/* 用户输入的客户端命令的最大长度 */
#define MAX_ARG 10			/* 命令所使用的最大参数个数 */
#define MAX_LENGTH 64		/* 每个参数或者命令的最大长度 */
#define NAME_LEN 256 /* Linux文件最大的文件名 */
/* 全局变量声明 */
/* 命令结构，存储用户输入的命令和命令所需的参数
* name : 命令名
* argv : 存储命令名和命令参数，其中argv[0]存储的也是命令名
*/
struct command_line{
	char *name;
	char *argv[MAX_ARG];
};
/* 函数接口声明区 */
/* input.c 和用户输入有关的函数*/
extern int split(struct command_line command, char cline[]);
/* command.c 命令处理函数 */
extern int do_connect(char *ip,struct sockaddr_in *sin, int *sock_fd); /* 处理connect命令 */
extern int do_get(const char *src, const char *dst, int sock_fd); /* 处理get命令 */
extern int do_put(const char *src, const char *dst, int sock_fd); /* 处理put命令 */
extern int do_serv_cd(char *path, int sock_fd); /* 处理!cd命令 */
extern int do_serv_ls(char *path, int sock_fd); /* 处理!ls命令 */
extern int do_cd(char * path);					 /* 处理cd命令 */
extern int do_ls(char *path);					 /* 处理ls命令 */
extern int do_bye(int sock_fd);				 /* 处理bye命令 */
