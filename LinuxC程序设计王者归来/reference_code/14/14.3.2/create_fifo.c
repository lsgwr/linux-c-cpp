#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[] )
{
	mode_t mode = 0666;    /*新创建的FIFO模式*/
	if ( argc != 2 ){
		/*向用户提示程序使用帮助*/
		printf("USEMSG: create_fifo {fifoname}\n"); 
		exit (1);
	}
	/* 使用mkfifo函数创建一个FIFO管道*/
	if ( ( mkfifo (argv[1], mode )) < 0) {  
		perror ( "failed to mkfifo" );
		exit ( 1 );
	}
	else
		printf ("you successfully create a FIFO name is : %s\n", argv[1]); 
		/* 输出FIFO文件的名称 */
	exit (0);
}
