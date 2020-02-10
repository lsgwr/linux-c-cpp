#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSZ 4096
struct msg{				/*声明消息结构体*/
	long msg_types;		/*消息类型成员*/    
	char msg_buf[511];	/*消息*/
};
int main( int argc, char * argv[] ) {
	long int	qid;
	int len;
	struct msg pmsg;
	if ( argc != 2 ){  /**/
		perror ( "USAGE: read_msg <queue ID>" );
		exit ( 1 );
	}
	qid = atoi ( argv[1] );   /*从命令行中获得消息队列的ID*/
	/*从指定队列读取消息 */
	len = msgrcv ( qid, &pmsg, BUFSZ, 0, 0 );
	if ( len > 0 ){
		pmsg.msg_buf[len] = '\0';						/*为消息添加结束符*/
		printf ("reading queue id :%05ld\n", qid );	/*输出队列ID*/
		/*该消息类型就是发送消息的进程ID*/
		printf ("message type : %05ld\n", pmsg.msg_types ); 
		printf ("message length : %d bytes\n", len );	/*消息长度*/
		printf ("mesage text: %s\n", pmsg.msg_buf);	/*消息内容*/
	}
	else if ( len == 0 )
		printf ("have no message from queue %ld\n", qid );
	else {
		perror ( "msgrcv");
		exit (1);
	}
	system("ipcs -q");	
	exit ( 0 ) ;
}
