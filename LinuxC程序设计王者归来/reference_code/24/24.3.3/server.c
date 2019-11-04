#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <stddef.h>
#include <time.h>
/* 使用/home/admin/connect.socket这个文件作为通信的套接字文件 */
#define PATH "/home/linux-c/connect.socket"
/* 如果超过这个时间，服务器进程将不处理客户端进程的连接请求 */
#define STALE 30
#define MAX 1024
/* 处理函数，用于将大写字符转换为小写字符。参数为需要转换的字符串 */
void my_fun(char * p)
{
	if(p == NULL) /* 空串 */
		return;
	for (; *p != '\0'; p++)
		if(*p >= 'A'&& *p <= 'Z') /* 判断字符并进行转换，也可以使用库函数 */
			*p = *p -'A'+'a';
}
/* 初始化函数，创建套接字，并且将该套接字绑定到一个地址（指定的文件）上
*  成功返回0，失败返回-1
*  lfd : 指向保存创建好的套接字的描述符的区域
*  path : 指定文件的路径，该文件必须是不存在的，否则bind函数会出错
*/
int init(int *lfd, char *path)
{
    int fd, len;
    struct sockaddr_un  un_addr;
    	/* 创建一个套接字，使用UNIX域，类型为数据流类型 */
    if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("fail to create socket");
       	return -1;
	}
	/* 如果套接字文件已经存在则删除，否则unlink函数出错，因此不检查unlink函数的返		回值 */
	unlink(PATH);
	/* 设置地址结构，该地址不再由IP地址和进程号组成，而是一个文件路径 */
	memset(&un_addr, 0, sizeof(un_addr));
	un_addr.sun_family = AF_UNIX;		/* 使用Unix域地址族 */
	strcpy(un_addr.sun_path, path);	/* 复制套接字文件的路径 */
	len = offsetof(struct sockaddr_un, sun_path) + strlen(path);
										/* 计算文件路径的长度 */
	/* 将套接字绑定到一个地址结构上，该套接字可以开始通信 */
	if (bind(fd, (struct sockaddr *)&un_addr, len) == -1){
		perror("fail to bind");
		goto err;
	}
	/* 开始监听，最大连接数为10 */
	if (listen(fd, 10) == -1){
		perror("fail to listen");
		goto err;
	}
	*lfd = fd;	/* 保存套接字的文件描述符 */
	return 0;	/* 执行到这里，正常返回 */
err:
	close(fd); /* 出错，关闭套接字 */
	return -1; /* 返回-1 */
}
int main(void)
{
	int lfd, cfd;
	time_t staletime; /* 测试客户端进程的时间 */
	struct sockaddr_un un_addr;
	struct stat statbuf;
	char buf[MAX];
	int len, n;
	if(init(&lfd, PATH) == -1) /* 调用初始化函数，创建监听套接字，并且开始监听 */
	exit(1);
	while(1){/* 服务器程序多半是死循环 */
		len = sizeof(struct sockaddr_un);
		/* 处理一个连接，创建连接套接字，得到客户端进程的套接字文件路径
		* 并将其保存在un_addr结构中，注意这里使用sockaddr_un结构的大小
		*/
		if ((cfd = accept(lfd, (struct sockaddr *)&un_addr, &len)) == -1){
			perror("fail to accept");
			exit(1);
		}
		/* 得到客户端文件的路径，并且设置结束符 */
		len -= offsetof(struct sockaddr_un, sun_path);
		un_addr.sun_path[len] = '\0';
		/* 得到文件的状态信息，为了验证客户端进程的通信时间
		* 客户端进程如果长期没有修改通信用的套接字文件，说明该客户端有可能已经结束通信
		* 下面分别验证文件的权限和修改时间，这些操作并不是必须的
		* 但是出于程序的完整性考虑，这些操作还是必要的
		*/
		if (stat(un_addr.sun_path, &statbuf) == -1) {
			perror("fail to get status");
			exit(1);
		}
		/* 检查文件的权限，通信用的套接字文件的权限必须是“rwx------”
		* 也就是说只有所有者用户可以有读、写和执行该文件的权限，其他用户没有
		* 这说明UNIX域套接字只能用于同一用户的进程之间的通信
		*/
		if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) || (statbuf.st_mode & S_IRWXU) != S_IRWXU) {
			printf("wrong permissions\n");
			exit(1);
		}
		/* 检查套接字文件的更新时间，超过30秒钟未作访问和修改
		* 说明客户端进程可能已经断开了连接，关闭连接套接字，结束连接
		*/
		staletime = time(NULL) - STALE;
		if (statbuf.st_atime < staletime || statbuf.st_ctime < staletime || statbuf.st_mtime < staletime){
			printf("client is too old\n");
			close(cfd);
			break;
		}
		/* 删除客户端的套接字文件
		* 该套接字文件由客户端进程在调用bind函数进行套接字绑定的时候生成
		*/
		if(unlink(un_addr.sun_path) == -1){
			perror("fail to unlink");
			exit(1);
		}
		if(read(cfd, buf, MAX) == -1){
			perror("fail to read");
			exit(1);
		}
		my_fun(buf); /* 调用大小写转换函数 */
		if(write(cfd, buf, n) == -1){ /* 将转换后的字串发给客户端进程 */
			perror("fail to write");
			exit(1);
		}
		close(cfd); /* 通讯结束，关闭套接字，准备下一次通信 */
	}
	/* 删除服务器进程的套接字文件 */
	if(unlink(PATH) == -1){
		perror("fail to unlink");
		exit(1);
	}
	close(lfd);
	return 0;
}
