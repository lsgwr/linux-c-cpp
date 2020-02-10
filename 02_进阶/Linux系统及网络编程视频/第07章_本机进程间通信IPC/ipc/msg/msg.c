#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <signal.h>

#define MSG_FILE "./msgfile"

#define MSG_SIZE 1024

struct msgbuf
{
	long mtype;         /* 放消息编号，必须 > 0 */
	char mtext[MSG_SIZE];  /* 消息内容（消息正文） */
};									


void print_err(char *estr)
{
	perror(estr);
	exit(-1);
}

int creat_or_get_msgque(void)
{
	int msgid = -1;
	key_t key = -1;
	int fd = 0;

	/* 创建一个消息队列的专用文件，ftok会用到这个文件的路径名 */
	fd = open(MSG_FILE, O_RDWR|O_CREAT, 0664);
	if(fd == -1) print_err("open fail");
	
	/* 利用存在的文件路径名和8位整形数，计算出key */
	key = ftok(MSG_FILE, 'a');
	if(key == -1) print_err("ftok fail");

	/* 利用key创建、或者获取消息队列 */
	msgid = msgget(key, 0664|IPC_CREAT);
	if(msgid == -1) print_err("msgget fail");

	return msgid;
}	

int msgid = -1;
void signal_fun(int signo)
{
	msgctl(msgid, IPC_RMID, NULL);
	remove(MSG_FILE);	
	
	exit(-1);
}

int main(int argc, char **argv)
{	
	int ret = -1;
	long recv_msgtype = 0;
	
	if(argc !=  2)
	{
		printf("./a.out recv_msgtype\n");
		exit(-1);
	}
	recv_msgtype = atol(argv[1]);
	
	
	msgid = creat_or_get_msgque();

	ret = fork();
	if(ret > 0) //发送消息
	{
		signal(SIGINT, signal_fun);
		struct msgbuf msg_buf = {0};
		while(1)
		{
			bzero(&msg_buf, sizeof(msg_buf));
			/* 封装消息包 */
			scanf("%s", msg_buf.mtext);
			printf("input snd_msgtype:\n");
			scanf("%ld", &msg_buf.mtype);

			/* 发送消息包 */
			msgsnd(msgid, &msg_buf, MSG_SIZE, 0);	
		}
	}
	else if(ret == 0)//接收消息
	{
		struct msgbuf msg_buf = {0};
		int ret = 0;
		while(1)
		{
			bzero(&msg_buf, sizeof(msg_buf));
			ret = msgrcv(msgid, &msg_buf, MSG_SIZE, recv_msgtype, 0);
			if(ret > 0) 
			{
				printf("%s\n", msg_buf.mtext);
			}	
		}
	}
	
		
	return 0;
}	
	
	
	
	
