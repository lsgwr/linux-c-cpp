// 父子线程必须使用各自的fd来操作同一个文件才能实现互斥，使用同一个fd达不到互斥效果
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>
#include "file_lock.h"


void *pth_fun(void *pth_arg)
{
	int fd = 0; // 次线程要用单独的fd

	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_error("open ./file fail");
	while(1)
	{
		SET_WRFLCK_W(fd, SEEK_SET, 0, 0);
		write(fd, "hello ", 6);	
		write(fd, "world\n", 6);
		UNLCK(fd, SEEK_SET, 0, 0);	
	}
	
	return NULL;	
}

int main(void)
{
	int fd = -1; // 父线程要用单独的fd
	int ret = -1;	
	pthread_t tid;

	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_error("open ./file fail");
	
	
	ret = pthread_create(&tid, NULL, pth_fun, NULL);
	if(ret == -1) print_error_thread("pthread_create fail", ret);
	
	
	while(1)
	{
		SET_WRFLCK_W(fd, SEEK_SET, 0, 0);
		write(fd, "hello ", 6);	
		write(fd, "world\n", 6);
		UNLCK(fd, SEEK_SET, 0, 0);	
	}
	
		
	return 0;
}
