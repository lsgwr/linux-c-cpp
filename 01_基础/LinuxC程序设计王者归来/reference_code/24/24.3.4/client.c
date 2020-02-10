#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
/* 使用/home/admin/connect.socket这个文件作为通信的套接字文件 */
#define PATH "/home/linux-c/connect.socket"
/* 客户端的套接字文件路径的目录，文件名为进程的进程ID */
#define C_PATH "/home/linux-c/"
#define MAX 1024
int main(void)
{
	int	cfd, len;
	struct sockaddr_un un_addr;
	char buf[MAX];
	if ((cfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){ /* 创建一个连接 */
		perror("fail to create socket");
		exit(1);
	}
	/* 设置客户端进程使用的套接字的路径名和套接字的域 */
	memset(&un_addr, 0, sizeof(struct sockaddr_un));
	un_addr.sun_family = AF_UNIX;
	/* 客户端的套接字文件名为默认目录 + 进程ID */
	sprintf(un_addr.sun_path, "%s%d", C_PATH, getpid());
	len = offsetof(struct sockaddr_un, sun_path) + strlen(un_addr.sun_path);
	/* 如果套接字文件已经存在则删除，否则unlink函数出错，因此不检查unlink函数的返回值 */
	unlink(un_addr.sun_path);
	/* 绑定客户端套接字文件，该文件由服务器端进程负责删除 */
	if (bind(cfd, (struct sockaddr *)&un_addr, len) == -1){
		perror("fail to bind");
		exit(1);
	}
	/* 改变套接字文件的权限为rwx------ */
	if (chmod(un_addr.sun_path, S_IRWXU) < 0) {
		perror("fail to change model");
		exit(1);
	}
	memset(&un_addr, 0, sizeof(struct sockaddr_un));
	un_addr.sun_family = AF_UNIX;
	strcpy(un_addr.sun_path, PATH); /* 服务器套接字文件的路径 */
	len = offsetof(struct sockaddr_un, sun_path) + strlen(un_addr.sun_path);
	/* 使用服务器的套接字文件进行连接 */
	if(connect(cfd, (struct sockaddr *)&un_addr, len) < 0) {
		perror("fail to connect");
		exit(1);
	}
	strcpy(buf,"China");
	if(write(cfd, buf, strlen(buf) + 1) == -1){ /* 发送字符串，该串包含‘\0’	结束符 */
	perror("fail to write");
		exit(1);
	}
	/* 读取服务器程序发回的串*/
	if(read(cfd, buf, MAX) == -1){
		perror("fail to read");
		exit(1);
	}
	printf("recive from server: %s\n", buf); /* 打印该串 */
	close(cfd);
	return 0;
}
