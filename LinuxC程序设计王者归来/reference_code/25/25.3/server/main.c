#include "common.h"
int main(void)
{
	struct sockaddr_in sin; /* 服务器端地址结构 */
	struct sockaddr_in cin; /* 客户端地址结构 */
	int lfd, cfd;
	socklen_t len = sizeof(struct sockaddr_in);
							 /* 十进制点分格式地址的长度，包括字符串结束符 */
	char buf[MAX_LINE];		 /* 命令缓冲区，存储发送给客户端的信息 */
	char str[ADDR_LEN];		 /* 十进制点分地址缓冲区 */
	int sock_opt = 1;		 /* 套接字选项 */
	int n; 
	pid_t pid; 
	if(init(&sin, &lfd, sock_opt) == -1)
							 /* 初始化程序，得到地址结构和监听套接字描述符 */
		exit(1);
	printf("waiting connections ...\n"); /* 打印提示信息 */
	while(1){ /* 死循环，处理客户端的请求 */
		if( (cfd = accept(lfd, (struct sockaddr *)&cin, &len)) == -1){ /* 接收请求 */
			perror("fail to accept");
			exit(1);
		}
		if( (pid = fork()) < 0){ /* 创建子进程*/
			perror("fail to fork");
			exit(1);
		}else if(pid == 0){	/* 子进程处理连接请求，父进程继续监听 */
			close(lfd);		/* 关闭监听套接字 */
			while(1){ /* 本程序的客户端是一个交互式程序，服务器端和客户端也是交			互的 */
				if(my_read(cfd, buf, MAX_LINE) == -1) /* 读取客户端的命令 */
					exit(1);
				/* 在用户发送的命令串中寻找合法的命令，找到则处理 */
				if(strstr(buf, "GET") == buf) /* get命令 */
					if(do_put(cfd, &buf[4]) == -1) /* 调用do_put函数进行													处理 */
						printf("error occours while putting\n");
				else if(strstr(buf, "PUT") == buf) /* put命令 */ 
					if(do_cd(cfd, &buf[4]) == -1) /* 调用do_put函数进行													处理 */
						printf("error occours while getting\n");
				else if(strstr(buf, "CD") == buf) /* cd命令 */
					if(do_ls(cfd ,&buf[4]) == -1)
						printf("error occours while changing directory\n");
				else if(strstr(buf, "LS") == buf) /* ls命令 */
					if(do_ls(cfd,&buf[4]) == -1)
						printf("error occours while listing\n");
				else if(strstr(buf, "BYE") == buf) /* bye命令 */
					break; /* 不调用相关函数处理，直接跳出循环 */
				else{ /* 未知命令，出错 */
					printf("wrong command\n");
					exit(1);
				}
			}
			close(cfd); /* 跳出循环后关闭连接套接字描述符，通信结束 */
			exit(0);	/* 子进程退出 */
		}else
			close(cfd); /* 父进程关闭连接套接字，继续监听 */
	}
	
	return 0; 			/* 服务器程序很少有退出的时候 */
}
