#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct msg{						/*声明消息结构体*/
	long msg_types;				/*消息类型成员*/
	char msg_buf[511];			/*消息*/
};
int main( void ) {
	int qid;
	int pid;
	int len;
	struct msg pmsg;			/*一个消息的结构体变量*/
	pmsg.msg_types = getpid();	/*消息类型为当前进程的ID*/
	sprintf (pmsg.msg_buf,"hello!this is :%d\n\0", getpid() ); /*初始化消息*/
	len = strlen ( pmsg.msg_buf );   /*取得消息长度*/
	if ( (qid=msgget(IPC_PRIVATE, IPC_CREAT | 0666)) < 0 ) {  /*创建一个消
																  息队列*/
		perror ( "msgget" );
		exit (1) ;
	}
	if ( (msgsnd(qid, &pmsg, len, 0 )) < 0 ){   /*向消息队列中发送消息*/
		perror ( "msgsn" );
		exit ( 1 );
	}
	printf ("successfully send a message to the queue: %d \n", qid);
	exit ( 0 ) ;
}
