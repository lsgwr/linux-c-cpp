#include "common.h"
/* init函数初始化服务器程序，成功返回0，失败返回-1
* sin : 地址结构的指针
* lfd : 
* opt : 套接字选项
*/
int init(struct sockaddr_in *sin, int *lfd, int sock_opt)
{
	bzero(sin, sizeof(struct sockaddr_in));
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = INADDR_ANY;
	sin->sin_port = htons(PORT);
	if( (tfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /* 创建监听套接字 */
		perror("fail to creat socket");
		return -1;
	}
	setsockopt(tfd, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof(int)); /* 	设置套接字选项 */
	/* 绑定客户端地址，具体地址没有限制 */
	if( (bind(tfd, (struct sockaddr *)sin, sizeof(struct sockaddr_in))) == 	-1){
		perror("fail to bind");
		return -1;
	}
	if( (listen(tfd, 20)) == -1){
		perror("fail to listen");
	return -1;
	}
	*lfd = tfd;
	return 0;
}
/* do_put函数，处理GET命令，成功返回0，失败返回-1
* GET命令的格式为：GET arg1
* 该命令传输客户端请求的文件，arg1表示需要的文件路径
* cfd : 连接套接字的描述符
* file : 客户端请求的文件的路径
*/
int do_put(int cfd, char *file)
{
	struct stat statbuf; /* 文件状态缓冲区 */
	int n, fd;
	int res = -1;		  /* 返回值 */
	if( (fd = open(file, O_RDONLY)) == -1){ /* 打开客户端请求的本地文件 */
		/* 打开失败则向客户端输出出错信息并将应答码设置为ERR
		* 出错信息格式为：应答码 出错信息
		*/
		my_write(cfd, "ERR open server file\n", strlen("ERR open server 			file\n"));  
		return res;		  /* 返回-1 */
	}
	if( (fstat(fd, &statbuf)) == -1){ /* 得到文件状态 */
		my_write(cfd, "ERR stat server file\n", strlen("ERR stat server 			file\n")		  /* 出错则发送错误信息 */
		goto end;
	}
	if(!S_ISREG(statbuf.st_mode)){ /* 如果被请求文件不是普通文件，则出错 */
		if(my_write(cfd, "ERR server path should be a regular file\n",
			strlen("ERR server path should be a regular file\n")) == -1) /* 			向客户端发送出错信息 */
			goto end;
		res = 0; /* 成功发送后do_put函数返回0，虽然出现了错误，但还是返回0 */
		goto end;
	}
	sprintf(buf, "OK %d", statbuf.st_size); /* 一切正常，发送应答信息，格式为：											 OK 发送文件的长度 */
	if(my_write(cfd, buf, strlen(buf)) == -1) /* 发送应答信息 */
		goto end;
	if ( (my_read(cfd, buf, MAX_LINE)) <= 0) /* 等待客户端的应答信息，应答码												   是RDY */
		goto end;
	while(1){ /* 开始传送文件内容 */
		n = read(fd, buf, MAX_LINE); /* 循环读取文件内容，直到文件结束 */
		if(n > 0)
			if(my_write(cfd, buf, n) == -1) /* 将读取的文件内容发送给客户端 */
				goto end;
		else if(n == 0) {  /* 文件已经到达结尾 */
			printf("OK\n");  /* 输出提示信息 */
			break;
		}else	{ /* 如果读取的字节数小于0则说明出错 */
			perror("fail to read");
			goto end;	 
		}
	}
	res = 0; /* 执行至此一切正常 */
end:
	close(fd); /* 关闭文件，注意不是关闭套接字 */
	return res;
}
/* do_get函数处理PUT命令，成功返回0，失败返回-1。
* PUT命令的格式为：PUT arg1 arg2
* 该命令将客户端的文件传送至服务器，arg1为文件的大小，arg2为传送文件在服务器端的文件路径
* cfd : 连接套接字的描述符
* file : 传送过来的文件在服务器端的存储路径
*/
int do_get(int cfd, char *file)
{
	struct stat statbuf; /* 文件状态缓冲区 */
	int n, fd, len;
int res = -1;
if( (fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1){ /* 打开文件 */
	/* 文件的打开方式是覆盖写，也就是说如果该文件已存在则覆盖。
	* 但是如果有一个同名的目录则无法覆盖，下面分支处理这种情况
	*/
	if(errno == EISDIR){
		if(my_write(cfd, "ERR server has a dir with the same name\n",
			strlen("ERR server has a dir with the same name\n")) == -1) /* 
			输出错误信息 */
			goto end;
		res = 0; /* 这种错误属于用户的不正确请求 */
		goto end;
	}else{ /* 其他的原因不能打开文件则是服务器程序的错误 */
		my_write(cfd, "ERR open server file\n", strlen("ERR open server 
		file\n")); /* 输出错误信息 */
		goto end;
		}
}
if( (fstat(fd, &statbuf)) == -1){ /* 得到文件状态 */
	my_write(cfd, "ERR stat server file\n", strlen("ERR stat server 
	file\n")); 						/* 输出错误信息 */
	goto end;
	}
len = statbuf.st_size;
if(!S_ISREG(statbuf.st_mode)){		/* 如果该文件不是普通文件则出错 */
	if(my_write(cfd, "ERR server path should be a regular file\n",
		strlen("ERR server path should be a regular file\n")) == -1) 
									/* 输出错误信息 */
		goto end;
	res = 0;
	goto end;
	}
if(my_write(cfd, "OK", 2) == -1)	/* 发送正确的应答码 */
	goto end;
	while(1){ 						/* 循环读传送过来的文件内容 */
	n = my_read(cfd, buf, MAX_LINE);
	if(n > 0){
		write(fd, buf, n); 			/* 写到指定的文件中 */
		len -= n;					/* 文件长度减少 */
	}else if(len == 0) {
		/* 文件没有剩余，表示传输完毕 */
		printf("OK\n");
		break;
	}else							/* 读取的字节数小于0，出错 */
		goto end;
	}
	res = 0;							/* 正常返回 */
end:
	close(fd); 
	return res;
}
/* do_cd函数处理CD命令，成功返回0，失败返回-1
* CD命令的格式为：PUT arg1
* 该命令进入指定的服务器端目录，arg1为指定目录的路径
* 参数为指定目录的路径
*/
int do_cd(char *path)
{
	if(chdir(path) == -1){ /* 进入指定的目录 */
		perror("fail to change directory\n");
		/* 出错则向客户端发送错误应答码和出错原因 */
		my_write(cfd, "ERR can't change directory\n", strlen("ERR can't change directory\n"));
		return -1;
	}
	my_write(cfd, "OK\n");
	return 0;
}
/* do_ls函数处理LS命令，成功返回0，失败返回-1
* LS命令的格式为：LS arg1
* 该命令列出当前服务器端目录下的文件，arg1为指定目录的路径
* 参数为指定目录的路径
*/
int do_ls(char *path)
{
	char cmd[128];
	char buf[NAME_LEN];
	struct stat statbuf; /* 文件状态缓冲区 */
	int n, fd;
	int res = -1;		  /* 返回值 */
	/* 拼接命令“ls path > temp.txt”，将文件列表写在temp.txt文件中 */
	sprintf(cmd, "ls %s > temp.txt ",path);
	system(cmd);		  /* 执行该命令 */
	if( (fd = open(“temp.txt”, O_RDONLY)) == -1){ /* 打开客户端请求的本地文件 	*/
		/* 打开失败则向客户端输出出错信息并将应答码设置为ERR。
		* 出错信息格式为：应答码 出错信息
		*/
		my_write(cfd, "ERR ls server file\n", strlen("ERR ls server 			file\n"));  
		return res;		  /* 返回-1 */
	}
	if( (fstat(fd, &statbuf)) == -1){ /* 得到文件状态 */
		my_write(cfd, "ERR stat server file\n", strlen("ERR stat server 			file\n") /* 出错则发送错误信息 */
		goto end;
	}
	if(!S_ISREG(statbuf.st_mode)){ /* 如果被请求文件不是普通文件，则出错 */
		if(my_write(cfd, "ERR server path should be a regular file\n",
			strlen("ERR server path should be a regular file\n")) == -1) 			/* 向客户端发送出错信息 */
			goto end;
		res = 0; /* 成功发送后do_put函数返回0，虽然出现了错误，但还是返回0 */
		goto end;
	}
	sprintf(buf, "OK %d", statbuf.st_size); /* 一切正常发送应答信息，格式为：												  OK 发送文件的长度 */
	if(my_write(cfd, buf, strlen(buf)) == -1) /* 发送应答信息 */
		goto end;
	if ( (my_read(cfd, buf, MAX_LINE)) <= 0) /* 等待客户端的应答信息，应答码												   是RDY */
		goto end;
	while(1){ /* 开始传送文件内容 */
		n = read(fd, buf, MAX_LINE);	    /* 循环读取文件内容，直到文件结束 */
		if(n > 0)
			if(my_write(cfd, buf, n) == -1)/* 将读取的文件内容发送给客户端 */
				goto end;
		else if(n == 0) {					/* 文件已经到达结尾 */
			printf("OK\n"); 				/* 输出提示信息 */
			break;
		}else	{ /* 如果读取的字节数小于0则说明出错 */
			perror("fail to read");
			goto end;	 
		}
	}
	res = 0; 	/* 执行至此一切正常 */
end:
	close(fd); /* 关闭文件，注意不是关闭套接字 */
	return res;
}

