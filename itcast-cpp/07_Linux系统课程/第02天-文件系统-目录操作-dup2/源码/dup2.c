#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#if 1

int main(void)
{
	int fd, save_fd;

	char msg[] = "It's a test!\n";

	fd = open("file1", O_RDWR|O_CREAT, 0644);	
	if(fd < 0){
		perror("open error");
		exit(1);
	}

	printf("------>fd = %d\n", fd);		//stdout	
	save_fd = dup(STDOUT_FILENO);		

	printf("save_fd = %d\n", save_fd);	
	write(save_fd, msg, strlen(msg));	//stdout	

	int ret = dup2(fd, STDOUT_FILENO);	
	printf("----->ret = %d\n", ret);	//file1 

	close(fd);							

	puts(msg);							

	return 0;
}


#else


int main(void)
{
	int fd, save_fd;

	char msg[] = "It's a test!\n";

	fd = open("file1", O_RDWR|O_CREAT, 0644);	
	if(fd < 0){
		perror("open error");
		exit(1);
	}

	printf("------>fd = %d\n", fd);		//新打开的文件描述符是3，里面保存指向feil1文件的指针
	save_fd = dup(STDOUT_FILENO);		//把文件描述符1所保存的stdout指针复制给文件描述符save_fd

	printf("save_fd = %d\n", save_fd);	//save_fd是文件描述符4,里面保存指向stdout的文件指针
	write(save_fd, msg, strlen(msg));	//向save_fd写，既是向stdout写,会写到屏幕

	//将fd(3)保存的指向file1的文件指针复制给STDOUT_FILENO(1),并覆盖1原来保存的文件指针
	int ret = dup2(fd, STDOUT_FILENO);	//结果是fd指向file1文件，STDOUT_FILENO(1)也指向file1文件
	printf(" -------> m = %d\n", ret);	//printf默认对应文件描述符1，但是现在1指向file1文件

	close(fd);							//fd(3)被关闭

	puts(msg);							

	return 0;
}


#endif


