#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int open_fun1(void)
{
	int fd = open("./file.txt", O_RDWR);
	if(-1 == fd)
	{
		printf("open fail: %d\n", errno);
		return 0;
	}
	return fd;
}	

int open_fun2(void)
{
	int fd = open("./file.txt", O_RDWR);
	if(-1 == fd)
	{
		printf("open fail: %d\n", errno);
		return 0;
	}
	return fd;
}	

int main(void)
{
	int fd1 = 0;
	int fd2 = 0;
	int flag = 0;

	fd1 = open_fun1();
	fd2 = open_fun2();
	
	/* 直接制定F_SETFL时，会直接使用新的标志，去修改掉就的标志
	   返回的是新设置的标志
	 */
	flag = O_WRONLY|O_TRUNC|O_APPEND;
	fcntl(fd1, F_SETFL, flag);

	/* 保留原有标志，然后在原有标志的基础上，叠加新标志 */
	flag = fcntl(fd2, F_GETFL, 0);//获取原有标志
	flag = flag | O_TRUNC | O_APPEND;//叠加
	fcntl(fd2, F_SETFL, flag); //设置回去
	
	
	
	
	while(1)
	{
		write(fd1, "hello\n", 6);
		sleep(1);
		write(fd2, "world\n", 6);
	}
		
	
	return 0;
}
