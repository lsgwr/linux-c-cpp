#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <limits.h>
#define BUFSZ PIPE_BUF
int main ( void )
{
	FILE *fp;
	char *cmd = "cat file1";				  /*shell 命令*/
	char buf[BUFSZ];
	if ((fp = popen( cmd , "r"))==NULL )	  /*创建子进程到父进程的数据管道*/
	{
		perror ( " failed to popen " ) ;
		exit ( 1 ) ;
	}
	while ((fgets(buf, BUFSZ, fp))!= NULL )  /*读出管道的数据*/
		printf ( "%s", buf ); 
	pclose ( fp ) ;							  /*关闭管道*/
	exit (0) ;
}
