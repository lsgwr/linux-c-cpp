#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
int main ( int argc ,char *argv[] ) 
{
	int qid ;
	if ( argc != 2 ){ /* 命令行参数出错 */
		puts ( "USAGE: del_msgq.c <queue ID >" );
		exit ( 1 );
	}
	qid = atoi ( argv[1] ); /* 通过命令行参数得到组ID */
	system( "ipcs -q");
	if ( ( msgctl( qid, IPC_RMID, NULL ) ) < 0 ){ /* 删除指定的消息队列 */
		perror ("msgctl");
		exit (1 );
	}
	system( "ipcs -q");
	printf ( "successfully removed %d  queue\n", qid ); /* 删除队列成功 */
	exit( 0 );
}
