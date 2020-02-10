#include "common.h"
/* 读取配置文件，对端口号和根目录进行配置。只在本文件内调用，使用static关键字进行声明
*  port ：端口号，path ：服务器程序的根目录
* 成功返回0，失败返回-1
*/
static int configuration(int *port, char *path)
{
	int i;
	FILE * fp; 
	char * p;
	char buf[50]; /* 文件内容的缓冲区 */
	fp = fopen("./config.ini", "r"); /* 打开配置文件，该文件放在服务器程序所在										   的目录下 */
	if(fp == NULL){
		perror("fail to open config.ini");
		return -1;
	}
	while(fgets(buf, 50, fp) != NULL){ /* 读取文件每一行的内容 */
		if(buf[strlen(buf)-1] != '\n'){ /* 判断文件格式 */
			printf("error in config.ini\n");
			return -1;  
		}else
			buf[strlen(buf)-1]='\0'; /* 添加结束符’\0’ */
		if(strstr(buf, "port") == buf){ /* 寻找“port”字样，读取端口号 */
		/* 端口号的配置格式为“prot: 8000”，注意“：”后面有一个空格，找到“：”的		位置 */
		if ((p = strchr(buf, ':')) == NULL){
				printf("config.ini expect ':'\n");
				return -1;	 
			}
			*port = atoi(p + 2); /* 跳过“：”和空格，得到端口号 */
			if(*port <= 0){
				printf("error prot\n");
				return -1;
			}
		}else if(strstr(buf, "root-path") == buf){ /* 得到根目录 */
			/*端口号的配置格式为“root-path: /root”
			* 注意“：”后面有一个空格，找到“：”的位置
			*/
			if((p = strchr(buf, ':')) == NULL){
				printf("config.ini expect ':'\n");
				return -1;	 
			}
			p++; /* 跳过‘: */
			/* 将根目录复制到path缓冲区内，该缓冲区在main函数中是可见的 */
			strcpy(path, p); 
		}else{
			printf("error in config.ini\n");
			return -1;  
		}
	}
	return 0;
}
/* init函数初始化服务器程序，成功返回0，失败返回-1
* sin : 地址结构的指针
* lfd : 
* opt : 套接字选项
*/
int init(struct sockaddr_in *sin, int *lfd, int *port, char *path)
{
	int tfd;
	configuration(port, path); /* 读取配置文件 */
	bzero(sin, sizeof(struct sockaddr_in));
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = INADDR_ANY;
	sin->sin_port = htons(PORT);
	if( (tfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /* 创建监听套接字 */
		perror("fail to creat socket");
		return -1;
	}
	/* 绑定客户端地址，具体地址没有限制 */
	if( (bind(tfd, (struct sockaddr *)sin, sizeof(struct sockaddr_in))) == -1){
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
/* 分析http协议头的第一行，得到请求文件方式和文件路径
* cfd：连接套接字， path：服务器程序的根目录，用于和解析出的文件名拼成完整的文件路径
* 成功返回0，失败返回-1
*/
int get_path(int cfd, char * path)
{
	char buf[MAX_LINE];
	if(my_read(cfd, buf, MAX_LINE) == -1) /* 读取HTTP协议头的第一行 */
		return -1;
	/* HTTP协议头第一行的格式为：“GET / HTTP/1.1”
	* 其中前三个字符为“GET”，第四个字符为空格
	* 第五个字符开始是所要求的文件的路径 
	*/
	if (strstr(buf, "GET") != buf) { /* 协议的开始说明取得文件的方式——“GET” 	*/
		DEBUG_PRINT("wrong request\n");
		return -1;
	}
	if ((buf[4] == '/')&&(buf[5]==' ')) /* 没有指定文件名，使用默认文件	“index.html” */
		strcat(path, "/index.html");
	else {
		strtok(&buf[4], " "); /* 否则使用客户端指定的文件名 */
		strcat(path, &buf[4]);
	}
	return 0;
}
/* 向客户端输出出错页面
* sock_fd是连接套接字
* 成功返回0，失败返回-1
*/
int error_page(int sock_fd)
{
	char err_str[1024];
	#ifdef DEBUG /* 调试时用于向客户端输出出错信息 */
		sprintf(err_str, "HTTP/1.1 404 %s\r\n", strerror(errno.h));
	#else 		 /* 发布版则不输出具体出错信息 */
		sprintf(err_str, "HTTP/1.1 404 Not Exsit\r\n");
	#endif
	if(my_write(sock_fd, err_str, strlen(err_str)) == -1) 
				/* http协议的协议头第1行 */
		return -1;
	/* 协议的第2行，说明页面的类型，该页面只输出出错信息，所以页面类型为文本类型 */
	if(my_write(sock_fd, "Content-Type: text/html\r\n\r\n", strlen 	"Content-Type: text/html\r\n\r\n") == -1)
		return -1;
	if(my_write(sock_fd, "<html><body> the file dose not exsit </body> 	</html>", 
		strlen("<html><body> the file dose not exsit </body></html>")) == 		-1) /* 输出html内容 */
		return -1;
	return 0;
}
/* 向客户端输出需要的页面
*  cfd：连接套接字，path：需要文件的完整路径
* 成功返回0，失败返回-1
*/
int write_page(int cfd, char * path)
{
	int n;	
	char buf[MAX_LINE]
	/* 协议头，和出错页面的格式一致 */
	if(my_write(cfd, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n")) 	== -1)
		return -1;
	/* 页面的类型，则需要根据文件的扩展名来进行判断 */
	if(my_write(cfd, "Content-Type: ", strlen("Content-Type: ")) == -1)
		return -1;
	n = strlen(path);
	/* 三种图片格式，表示图片类型 */
	if(strcasecmp(&path[n-3], "jpg") == 0 || (strcasecmp(&path[n-4], "jpeg") 	== 0)) /* jpg图片 */
		if(my_write(cfd, "image/jpeg", strlen("image/jpeg")) == -1)
			return -1;
	else if(strcasecmp(&path[n-3], "gif")==0) /* gif图片 */
		if(my_write(cfd, "image/gif", strlen("image/gif")) == -1)
			return -1;
	else if(strcasecmp(&path[n-3], "png")==0) /* png图片 */
		if(my_write(cfd, "image/png", strlen("image/png")) == -1)
			return -1;
	else /* 纯文本类型 */
		if(my_write(cfd, "text/html", strlen("text/html")) == -1)
			return -1;
	if(my_write(cfd, "\r\n\r\n", 4) == -1) /* 添加协议结尾，最后多出一个“\r\n” 	*/
		return -1; 
	while ((n = read(fd, buf, MAXL_INE)) > 0) /* 传输文件内容 */
		if(my_write(cfd, buf, n) == -1)
			return -1;
	return 0;
}

