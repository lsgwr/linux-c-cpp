#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void)
{
	int *p;
	pid_t pid;
	
	int fd;
	fd = open("/dev/zero", O_RDWR);

	p = mmap(NULL, 400, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);

	if(p == MAP_FAILED){		//注意:不是p == NULL
		perror("mmap error");
		exit(1);
	}

	pid = fork();				//创建子进程
	if(pid == 0){
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	munmap(p, 4);				//释放映射区

	return 0;
}
