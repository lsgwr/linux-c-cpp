#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "file_lock.h"
#include <sys/file.h>



void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

void *pth_fun(void *pth_arg)
{
	int fd = 0;

	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_err("open ./file fail", __LINE__, errno);
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
	int fd = -1;
	int ret = -1;	
	pthread_t tid;

	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_err("open ./file fail", __LINE__, errno);
	
	
	ret = pthread_create(&tid, NULL, pth_fun, NULL);
	if(ret == -1) print_err("pthread_create fail", __LINE__, ret);
	
	
	while(1)
	{
		SET_WRFLCK_W(fd, SEEK_SET, 0, 0);
		write(fd, "hello ", 6);	
		write(fd, "world\n", 6);
		UNLCK(fd, SEEK_SET, 0, 0);	
	}
	
		
	return 0;
}



