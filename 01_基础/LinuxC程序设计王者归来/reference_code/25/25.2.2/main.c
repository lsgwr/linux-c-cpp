#include "common.h"
int main(void)
{
	char cline[COMMAND_LINE];		/* 缓冲区，存储用户输入的命令 */
	struct command_line command;	/* 命令结构，存储分解后的命令 */
	int sock_fd;
	struct sockaddr_in sin;			/* 服务器端的地址结构 */
	printf("myftp$: ");				/* 打印提示符 */
	fflush(stdout);					/* 保证提示符显示 */
	while(fgets(cline, MAX_LINE, stdin) != NULL){ /* 得到一行命令 */
		if(split(command, cline) == -1) /* 将命令拆分为命令名和命令参数的形式*/
			exit(1);
		/* 根据命令名作命令处理，比较命令名和每一个合法命令，匹配则处理 */
		if(strcasecmp(command.name, "get") == 0){ /* get命令 */
			if(do_get(command.argv[1], command.argv[2], sock_fd) == -1)
				exit(1); /* 命令处理出错则退出 */
		}else if(strcasecmp(command.name, "put") == 0){ /* put命令 */
			if(do_put(command.argv[1], command.argv[2], sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "cd") == 0){ /* cd命令 */
			if(do_cd(command.argv[1]) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "!cd") == 0){ /* !cd命令 */
			if(do_serv_cd(command.argv[1], sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "ls") == 0){ /* ls命令 */
			if(do_ls(command.argv[1]) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "!ls") == 0){ /* !ls命令 */
			if(do_serv_ls(command.argv[1], sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "connect") == 0){ /* connect			命令 */
			if(do_connect(command.argv[1], &sin, &sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "bye") == 0){ /* bye命令 */
			if(do_bye(sock_fd) == -1)
				exit(1);
			break; /* 向服务器端发送退出信息后，则跳出循环，退出程序 */
		}else{ /* 错误命令，打印程序的用法 */
			printf("wrong command\n");
			printf("usage : command arg1, arg2, ... argn\n");
		}
		printf("myftp$: "); /* 再次打印提示符，准备接受新的命令 */
		fflush(stdout);
	}
	if(close(sock_fd) == -1){ /* 执行bye命令后执行到这里，关闭通信用套接字 */
		perror("fail to close");
		exit(1);
	}
	return 0; /* 程序正常退出 */
}
