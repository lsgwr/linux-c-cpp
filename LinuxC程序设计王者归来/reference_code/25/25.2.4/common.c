#include "common.h"
/* do_connect函数，处理connect命令。成功返回0，失败返回-1
* connec命令的形式为：connect arg1
* 该命令用于和服务器进行连接，arg1是服务器的IP地址
 * ip : 字符指针，指向服务器的地址，是一个十进制点分字符串
 * sin : 地质结构指针，指向服务器地址结构，在connect函数中填充
 * sock_fd : 整型指针，指向通信用套接字描述符，该套接字在connct函数中设置，将描述符传回
 * main函数、供其他函数使用
 */
int do_connect(char *ip,struct sockaddr_in *sin, int *sock_fd)
{
	int sfd; /* 临时的套接字描述符 */
	bzero(&sin, sizeof(struct sockaddr_in)); /* 将地址结构清空 */
	sin.sin_family = AF_INET;				   /* 使用IPv4地址族 */
	/* 将点分十进制形式的IP地址转换成为二进制形式的地址，并且存储在地址结构中 */
	if(inet_pton(AF_INET, ip, &sin.sin_addr) == -1){
		perror("wrong format of ip address"); /* 如果地址格式为非法则出错 */
		return -1;
	}
	sin.sin_port = htons(PORT); /* 将端口号转换成为网络字节序存储在地址结构中 */
	if(sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ /* 创建套接字 */
		perror("fail to creat socket");
		return -1;	
	}
	/* 使用该套接字，和填充好的地址结构进行连接 */
	if(connect(sfd, (struct sockaddr *)sin, sizeof(struct sockaddr_in)) == 	-1){
		perror("fail to connect");
		return -1;
	}
	*sock_fd = sfd; /* 将sfd保存的套接字的描述符赋值给sock_fd所指向区域返回 */
	return 0;
}
/* do_get函数，处理get命令，成功返回0，失败返回-1
* get命令的形式为：get arg1 arg2
* 该命令从服务器端取得文件，arg1表示源文件，arg2表示目的路径，如果该文件已存在则覆盖
* src : 源文件，是一个绝对路径
* dst : 目的目录，是一个绝对的路径
* sock_fd : 通信用的套接字描述符
*/
int do_get(const char *src, const char *dst, int sock_fd)
{
	char *dst_file;		/* 目的路径 */
	char *p;
	struct stat statbuf;/* 文件状态缓冲区 */
	int n, fd;
	char buf[MAX_LINE];/* 命令缓冲区，存储发送给服务器端的命令 */
	int len;
	int res = -1;		/* 返回值默认的值为-1 */
	if(src == NULL || dst == NULL){/* 检查源文件和目的地址是不是空串 */
		printf(wrong command\n);	/* 是空串则报错 */
		return -1;
	}
	/* 如果源文件路径的最后一个字符是‘/’，则说明源文件不是一个普通文件，而是一个目录 	*/
	if(src[strlen(src)-1]=='/'){
		printf("source file should be a regular file\n");
		return -1;
	}
	/* 为最终的目的文件路径分配内存空间
	* 文件路径由目标目录和源文件的文件名组成
	* 所以该缓冲区的大小最大是两个文件路径的长
	*/
	if( (dst_file = (char *)malloc(strlen(dst) + strlen(src))) == NULL){ 
		perror("fail to malloc");
		return -1;			  /* 如果内存分配不成功则返回-1 */
	}
	strcpy(dst_file, dst);	  /* 将目标目录复制到dst_file缓冲区中 */
	/* 如果目标目录的结尾不是‘/’，则添加‘/’，例如/home/admin—>/home/admin/ */
	if(dst_file[strlen(dst_file) - 1] != '/')
		strcat(dst_file, "/");
	p = rindex(src, '/'); 		/* 取源文件路径中最后一个‘/’，其后面是文件名 */
	strcat(dst_file, p + 1);	/* 跳过‘/’，得到源文件文件名 */
	/* 如果目标文件不存在则创建该文件，使用权限字“0644”
	* 该权限表示所有者拥有读写权限而组用户和其他用户只有读权限
	* 如果该文件存在，则将文件截短为0打开，覆盖原文件
	*/
	if((fd = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
		perror("fail to open dst-file");
		goto end2; /* 打开文件失败，退出时只需要释放dst_file的内存，而不需要关闭		文件 */
	}
	if(fstat(fd, &statbuf) == -1){ /* 取目标文件的文件状态 */
		perror("fail to stat dst-file");
		goto end1;
	}
	/* 如果目标文件已经存在，且不是一个普通文件，则无法传输
	* 因为这样会造成将已经存在的目录等其他特殊文件覆盖
	*/
	if(!S_ISREG(statbuf.st_mode)){
		printf("dst-file should be a regular file");
		goto end1;
	}
		sprintf(buf, "GET %s", src); /* 准备向服务器端发送GET命令 */
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) /* 发出命令 */
		goto end1;									  /* 出错则退出 */
	if( (n = my_read(sock_fd, buf, MAX_LINE)) <= 0){ /* 接收服务器端发回的确													   认信息 */
		goto end1;
	}
	if(buf[0] == 'E'){ /* 如果收到的信息是ERR，表示出错 */
		write(STDOUT_FILENO, buf, n); /* 向屏幕输出服务器发来的出错信息 */
		res = 0;
		goto end1;
	}
	/* 如果对没有出错，服务器反馈的信息格式为“OK 请求文件的文件大小”
	* 跳过字符串“OK”和一个空格，从第三个字符开始，取得文件的长度 
	*/
	len = atoi(&buf[3]);
	/* 向服务器发出准备好的信息，服务器接收到此信息后开始传送文件的内容 */
	if(my_write(sock_fd, "RDY", 3) == -1)
		goto end1;
	while(1){ /* 循环读，直到读完所有的文件内容 */
		n = my_read(sock_fd, buf, MAX_LINE); /* 读服务器传送来的内容 */
		if(n > 0){ /* 读到的字节数大于0，说明正常 */
			write(fd, buf, n); /* 将读到的内容写到打开的目标文件中去 */
			len -= n; /* 文件总长度减少 */
		}else if(len == 0){ /* 读到的字节数等于0，说明通信已经结束 */
			/* 如果请求的文件已经读完，则正常结束此次命令的执行 */
			printf("OK\n"); 
			break;
		}else /* 读到的字节数小于0，出错 */
			goto end1;
	}
	res = 0; /* 运行到此，则函数正常返回，返回值为0 */
end1:
	free(dst_file); /* 释放动态分配的内存空间 */
end2:
	close(fd); /* 关闭文件 */
	return res;
}
/* do_serv_cd函数，处理!cd命令，成功返回0，失败返回-1
 * !cd命令的格式为：!cd arg1
 * 该命令用于进入服务器端的指定目录，arg1表示指定的目录
 * path : 指定的目录，这是一个绝对路径
 * sock_fd ：通信用的套接字描述符
*/
int do_serv_cd(char *path, int sock_fd)
{
	char buf[MAX_LINE];
	
	sprintf(buf, "CD %s", path); /* 向服务器端发送CD命令 */
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) 
								  /* 将命令和指定的路径发送给服务器 */
		return -1;
	if( (n = my_read(sock_fd, buf, MAX_LINE)) <= 0) 
								  /* 读取服务器发送的应答信息 */
		return -1;
if(buf[0] == 'E') 			  /* 应答码为“ERR”,表示出错 */
		write(STDOUT_FILENO, buf, n); /* 将出错信息输出到标准输出 */
	return 0;
}
/* do_serv_ls执行!ls命令，成功返回0，失败返回-1
 * !ls命令的格式为：!ls arg1
 * 该命令用于列出服务器端指定目录的所有文件，arg1表示置顶的目录
 * path : 指定的目录，这是一个绝对路径
 * sock_fd : 通信用的套接字描述符
*/
int do_serv_ls(char *path, int sock_fd)
{
	char buf[MAX_LINE];
	int len;
	sprintf(buf, "LS %s", path); /* 向服务器发送LS命令 */
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) /* 将命令和指定的目录发														  送给服务器 */
		return -1;
	if( (n = my_read(sock_fd, buf, MAX_LINE)) <= 0) /* 读取服务器端的应答码 */
		return -1;
	if(buf[0] == 'E'){ /* 应答码为“ERR”,表示出错 */
		write(STDOUT_FILENO, buf, n); /* 将出错信息输出到标准输出 */
		return 0;
	}
	len = atoi(&buf[3]); /* 跳过应答码“OK”和空格，得到本次传送内容的字节数 */
	if(my_write(sock_fd, "RDY", 3) == -1) /* 通知服务器准备接收*/
		return -1;
	while(1){ /* 循环读，直到读完所有服务器传送过来的内容 */
		n = my_read(sock_fd, buf, MAX_LINE); 
		if(n > 0){ /* 服务器将列出的文件列表传送过来，客户端读取该列表并且输出到屏						幕输出 */
			write(STDOUT_FILENO, buf, n);
			len -= n; /* 接收内容总长度减少 */
		}else if(len == 0){ /* 网络通信关闭 */
			/* 没有剩余，表示传输完毕 */
			printf("OK\n");
			break; /* 通信已经结束 */
		}else /* my_read函数的返回值小于0，则返回出错 */
			return -1;
	}
	return 0;
}
/* do_bye函数处理bye命令，成功返回0，失败返回-1
 * bye命令格式为：bye
 * 该命令向服务器端发送关闭连接请求的命令，之后退出客户端程序
 * sock_fd : 通信用的taojiezi 描述符
*/
int do_bye(int sock_fd)
{
	char buf[MAX_LINE];
	sprintf(buf, "BYE"); /* 向服务器端发送BYE命令 */
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) /* 失败则退出 */
		return -1;
	return 0;
}
/* do_put函数处理put命令，成功返回0，失败返回-1
 * put命令的格式为：put arg1 arg2
* 该命令用于向服务器端传输文件，arg1表示源文件，arg2表示目的路径，如果该文件已存在则覆盖
* src : 源文件，是一个绝对路径
* dst : 目的目录，是一个绝对的路径
* sock_fd : 通信用的套接字描述符
*/

int do_put(const char *src, const char *dst, int sock_fd)
{
	char *dst_file;			/* 目的路径，在服务器端 */
	struct stat statbuf;	/* 文件状态缓冲区 */
	int n, fd; 
	int res = -1;			/* 返回值默认的值为-1 */
	char buf[MAX_LINE];		/* 命令缓冲区，存储发送给服务器端的命令 */
	if(src == NULL || dst == NULL){ /* 检查源文件和目的地址是不是空串 */
		printf(wrong command\n);
		return -1;
	}
	if(src[strlen(src)-1]=='/'){ /* 传输的文件必须指定文件名 */
		printf("source file should be a regular file\n");
		return -1;
	}
	if((dst_file = malloc(strlen(dst)+strlen(src)+2)) == NULL){ /* 为最终		的目的文件路径分配内存空间 */
		perror("fail to malloc");
		return -1;
	}
	
	strcpy(dst_file, dst);
	if(dst_file[strlen(dst_file)-1] != '/')
		strcat(dst_file, "/");
	p = rindex(src, '/');
	strcat(dst_file, p + 1); /* 拼接得到完整的目的路径 */
	if((fd = open(src, O_RDONLY)) == -1){ /* 打开需要传输的文件 */
		perror("fail to open src-file");
		goto end1;
	}
	if(fstat(fd, &statbuf) == -1){ /* /* 取源文件的文件状态 */ */
		perror("fail to stat src-file");
		goto end2;
	}
	if(!S_ISREG(statbuf.st_mode)){ /* 只有普通文件能够传输 */
		fputs("src-file should be a regular file\n", stderr);
		goto end2;
	}
	/* 准备向服务器端发送PUT命令 */
	sprintf(buf, "PUT %d %s", statbuf.st_size, server_file);
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) /* 发出命令 */
		goto end2;
	if((my_read(sock_fd, buf, MAX_LINE)) <= 0) /* 接收服务器端发回的确认信息 */
		goto end2;
	if(buf[0]=='E'){ /* 如果收到的信息是ERR，表示出错 */
		write(STDOUT_FILENO, buf, n); /* 向屏幕输出服务器发来的出错信息 */
		goto end2;
	}
	/* 否则得到“RDY”应答，准备向服务器端传输文件 */
	while(1){ /* 循环读取文件的内容，直到文件结束 */
		n = read(fd, buf, MAX_LINE); /* 读取本地的源文件 */
		if(n > 0)
			if(my_write(sock_fd, buf, n) == -1) /* 向服务器端输出读入的文件内												 容 */
				goto end2;
		else if(n == 0){ /* 文件已到达结尾，跳出循环 */
			printf("OK\n");
			break;
		}else{ /* 读操作出错 */
			perror("fail to read\n");
			goto end2;
		}
	}
	res = 0; /* 运行到此，则函数正常返回，返回值为0 */
end1:
	close(fd);		 /* 关闭文件 */
end2:
	free(dst_file); /* 释放dst_file指向的内存 */
	return res; 
}
/* do_cd函数处理cd命令，成功返回0，失败返回-1
 * cd命令的格式为：cd arg1
* 该命令用于进入客户端的指定目录，arg1是指定的目录
* path : 指定的目录，这是一个绝对路径
 */
int do_cd(char * path)
{
	if(chdir(path) == -1){ /* 改变当前工作目录 */
		perror("fail to change directory\n");
		return -1;
	}
	
	return 0;
}
/* do_ls函数处理ls命令，成功返回0，失败返回-1
* ls命令的格式为：ls arg1
* 该命令用于列出客户端的指定目录中的文件，arg1是指定的目录
* path : 指定的目录，这是一个绝对路径
*/
int do_ls(char *path)
{	
	char cmd[128];
	char buf[NAME_LEN]
	FILE *fp;
	/* 拼接命令“ls path > temp.txt”，将文件列表写在temp.txt文件中 */
	sprintf(cmd, "ls %s > temp.txt ",path);
	system(cmd);				  /* 执行该命令 */
	fp = fopen("temp.txt", "r"); /* 打开列有文件列表的临时文件 */
	if(fp == NULL){
		perror("fail to ls");
		return -1;
	}
	while(fgets(buf, NAME_LEN, fp) == NULL) /* 输出文件列表 */
		printf("%s", buf);
	fclose(fp);
	return 0;
}

