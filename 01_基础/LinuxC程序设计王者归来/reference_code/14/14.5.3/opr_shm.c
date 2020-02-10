#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
int main ( int argc, char *argv[] )
{
	int shm_id ;
	char * shm_buf;
	if ( argc != 2 ){ /* 命令行参数错误 */
		printf ( "USAGE: atshm <identifier>" );   /*打印帮助消息*/
		exit (1 );
	}
	shm_id = atoi(argv[1]);						   /*得到要引入的共享内存段*/
	/*引入共享内存段，由内核选择要引入的位置*/
	if ( (shm_buf = shmat( shm_id, 0, 0)) < (char *) 0 ){
		perror ( "shmat" );
		exit (1);
	}
	printf ( " segment attached at %p\n", shm_buf );   /*输出导入的位置*/
	system("ipcs -m");
	sleep(3);						/* 休眠 */
	if ( (shmdt(shm_buf)) < 0 ) {	/*与导入的共享内存段分离*/
		perror ( "shmdt");
		exit(1);
	}
	printf ( "segment detached \n" );
	system ( "ipcs -m " );			/*再次查看系统IPC状态*/
	exit ( 0 );
}
