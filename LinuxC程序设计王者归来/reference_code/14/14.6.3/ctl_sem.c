#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
int main( void )
{
	int sem_id ;
	int nsems = 1;
	int flags = 0666;
	sem_id = semget ( IPC_PRIVATE, nsems, flags );	/*创建一个信号量集*/
	if ( sem_id < 0 ){								/* 创建信号两失败 */
		perror ( "semget" );
		exit ( 1 );
	}
	printf ( "successfully created a semaphore: %d \n", sem_id );
													/*输出创建的信号量的ID */
	system ( "ipcs -s" );							/*查看系统IPC状态*/
	if ( (semctl (sem_id, 0, IPC_RMID)) < 0 ) {		/* 删除指定信号量集*/
		perror ( "semctl" );
		exit (1 );
	}
	else {
		printf ( "semaphore removed \n");
		system ( "ipcs -s ");						/*查看系统IPC状态*/
	}
	exit ( 0 );
}
