#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
int main( void )
{
	int sem_id;
	int nsems = 1;
	int flags = 0666;
	struct sembuf buf;
	sem_id = semget(IPC_PRIVATE, nsems, flags);	/*创建一个新的信号量集*/
	if ( sem_id < 0 ){
		perror( "semget ") ;
		exit (1 );
	}
	/*输出相应的信号量集标识符*/
	printf ( "successfully created a semaphore : %d\n", sem_id );	
	buf.sem_num = 0;      							/*定义一个信号量操作*/
	buf.sem_op = 1;									/*执行释放资源操作*/
	buf.sem_flg = IPC_NOWAIT;						/*定义semop函数的行为*/
	if ( (semop( sem_id, &buf, nsems) ) < 0) {		/*执行操作*/
		perror ( "semop");
		exit (1 ); 
	}
	system ( "ipcs -s " );							/*查看系统IPC状态*/
	exit ( 0 );
}
