#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUFSZ PIPE_BUF
void err_quit(char * msg){
	perror( msg );
	exit(1);
}
int main ( void ) 
{
	int fd[2];
	char buf[BUFSZ];		/* 缓冲区 */
	pid_t pid;
	int len;
	if ( (pipe(fd)) < 0 )	/*创建管道*/
		err_quit( "pipe" );
	if ( (pid = fork()) < 0 )					/*创建第一个子进程*/
		err_quit("fork");
	else if ( pid == 0 ){						/*子进程中*/
		close ( fd[0] );						/*关闭不使用的文件描述符*/
		write(fd[1], "hello brother!\n", 15 );	/*发送消息*/
		exit(0);
	}
	if ( (pid = fork()) < 0 )					/*创建第二个子进程*/
		err_quit("fork");
	else if ( pid > 0 ){						/*父进程中*/
		close ( fd[0] );
		close ( fd[1] );
		exit ( 0 );
	}
	else {										/*子进程中*/
		close ( fd[1] );						/*关闭不使用的文件描述符*/
		len = read (fd[0], buf, BUFSZ );		/*读取消息*/
		write(STDOUT_FILENO, buf, len);
		exit(0);
	}
}
