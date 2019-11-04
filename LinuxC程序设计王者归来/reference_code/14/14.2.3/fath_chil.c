#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#define BUFSZ PIPE_BUF  /* PIPE_BUF管道默认一次性读写的数据长度*/
int main ( void ) 
{
	int fd[2];
	char buf[BUFSZ];
	pid_t pid;
	ssize_t len;
	if ( (pipe(fd)) < 0 ){						/*创建管道*/
		perror ( "failed to pipe" );
		exit( 1 );
	}
	if ( (pid = fork()) < 0 ){					/* 创建一个子进程 */
		perror ( "failed to fork " );
		exit( 1 );
	}
	else if ( pid > 0 ){
		close ( fd[0] );						/*父进程中关闭管道的读出端*/
		write (fd[1], "hello my son!\n", 14 );	/*父进程向管道写入数据*/
		exit (0);
	}
	else {
		close ( fd[1] );						/*子进程关闭管道的写入端*/
		len = read (fd[0], buf, BUFSZ );		/*子进程从管道中读出数据*/
		if ( len < 0 ){
			perror ( "process failed when read a pipe " );
			exit( 1 );
		}
		else
			write(STDOUT_FILENO, buf, len);	/*输出到标准输出*/
		exit(0);
	}
}
