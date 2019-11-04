#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#define MAX 100
int main(void)
{
	int sockfd[2]; /* 用于保存UNIX域套接字描述符的数组 */
	pid_t pid;
	char buf[MAX];
	int n;
	/* 创建一对未命名的UNIX域套接字，其类型为数据流方式的
	* sockfd[0]为读端，sockfd[1]为写端
	 */
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) == -1){
		perror("fail to create socket");
		exit(1);
	}
	/* 创建一个子进程，父子进程使用刚刚创建的未命名的UNIX域套接字进行通信 */
	pid = fork();
	if(pid < 0){ /* 创建子进程出错 */
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){ /* 子进程 */
		close(sockfd[0]); /* 关闭读端，子进程向父进程输出内容 */
		strcpy(buf, "hello parent");
		n = strlen(buf);
		if(write(sockfd[1], buf, n) == -1){ /* 向父进程发送信息 */
			perror("fail to write");
			exit(1);
		}
		
		printf("the child done\n"); /* 输出提示信息，进程终止运行 */
	}else{
		close(sockfd[1]); /* 关闭写端，父进程读取子进程的输出 */
		
		if(read(sockfd[0], buf, MAX) == -1){ /* 读取子进程发送给父进程的信息 */
			perror("fail to read");
			exit(1);
		}
		n = strlen(buf);
		buf[n] = '\0'; /* 添加结束符，便于输出该信息 */
		printf("recive from child : %s\n", buf); /* 输出子进程发送给父进程的			信息 */
		
		if(wait(NULL) == -1){ /* 回收子进程的结束状态 */
			perror("fail to wait");
			exit(1);
		}
		printf("the parent done\n"); /* 输出父进程结束运行的提示信息 */
	}
	return 0;
}
