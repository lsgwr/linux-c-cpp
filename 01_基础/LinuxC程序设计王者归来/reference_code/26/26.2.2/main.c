#include "common.h"
int main(void)
{
	struct sockaddr_in sin, cin;
	socklen_t len = sizeof(cin);
	int lfd, cfd, fd;
	pid_t pid;
	int sock_opt = 1;			 /* 套接字选项 */
	int port;
	char path[MAX_LINE];		 /* 文件路径缓冲区 */
	struct stat statbuf;		 /* 文件状态结构 */
	signal(SIGCHLD, SIG_IGN);	 /* 安装信号处理函数 */
	signal(SIGPIPE, SIG_IGN);	 /* 安装信号处理函数 */
	printf("initializing ...\n");
	if(init(&sin, &lfd, &port, path) == -1){ /* 初始化 */
		DEBUG_PRINT("error during initializing\n");
		exit(1);
	}
	while (1){ /* 死循环，不断地接受并且处理连接请求 */
		DEBUG_PRINT ("waiting connection ...\n");
		cfd = accept(lfd, (struct sockaddr *)&cin, &len); /* 创建连接套接字 */
		if(cfd == -1){
			perror("fail to accept");
			exit(1);
		}
		pid = fork();	/* 创造子进程，用于并发处理请求 */
		if(pid < 0){	/* fork出错 */
			perror("fail to fork");
			exit(1);
		}else if(pid == 0){ /* 子进程，处理连接请求 */
			close(lfd);		 /* 处理连接，关闭监听套接字 */
	if(get_path(cfd, path) == -1){	/* 分析客户端发来的信息，得到请求文											件的路径 */
		DEBUG_PRINT ("error during geting filepath\n");
		exit(1);
	}
	if(fstat(fd, &statbuf) < 0){ /* 得到该文件的状态 */
		perror("fail to get file status");
		exit(1);
	}
	if(!S_ISREG(statbuf.st_mode)){ /* 非普通文件 */
		if(error_page(cfd) == -1){ /* 输出出错页面 */
			DEBUG_PRINT ("error during writing error-page\n");
			
			close(cfd);
			
			exit(1); /* 输出该页面出错，则异常退出 */
		}
		
		close(cfd); /* 关闭连接套接字，连接结束 */
		
		exit(0);	/* 子进程正常退出 */
	}
	if(statbuf.st_mode & S_IXOTH){ /* 如果是可执行文件，说明是一个CGI	文件 */
		/* CGI文件将输出作为结果回送给客户端，所以将连接套接字重定向到标准输出 */
		dup2(cfd, STDOUT_FILENO);
		
		if(execl(path, path, NULL) == -1){ /* 执行该CGI文件 */
			perror("fail to exec");
			exit(1);
		}
			}
			/* 非CGI文件，则需要回送文件内容给客户端 */
			if((fd = open(path, O_RDONLY)) < 0){ /* 打开文件 */
				if(error_page(cfd) == -1){ /* 输出出错处页面 */
					DEBUG_PRINT ("error during writing error-page\n");
					close(cfd); /* 关闭连接套接字 */
					exit(1);	/* 进程退出 */
				}
				close(cfd);
				exit(0);		/* 子进程正常退出 */
			} 
			if(write_page(cfd, path) == -1){ /* 输出页面 */
				DEBUG_PRINT ("error during writing page\n");
				exit(1);
			}
			close(fd);	/* 关闭文件 */
			close(cfd); /* 关闭连接套接字，服务器端主动关闭，表示数据传输完毕 */
			exit(0);	/* 子进程正常退出 */
		}else 			/* 父进程，继续监听连接请求 */
			close(cfd); /* 继续监听，关闭连接套接字 */
	}
	return 0;
}

