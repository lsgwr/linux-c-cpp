#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

void *smalloc(size_t size)
{
	void *p;

	p = mmap(NULL, size, PROT_READ|PROT_WRITE, 
			MAP_SHARED|MAP_ANON, -1, 0);
	if (p == MAP_FAILED) {		
		p = NULL;
	}

	return p;
}

void sfree(void *ptr, size_t size)
{
	munmap(ptr, size);
}

int main(void)
{
	int *p;
	pid_t pid;
	
	p = smalloc(4);

	pid = fork();				//创建子进程
	if (pid == 0) {
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	sfree(p, 4);

	return 0;
}
