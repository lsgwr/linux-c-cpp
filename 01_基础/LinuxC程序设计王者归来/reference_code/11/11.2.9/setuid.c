#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	FILE *fp;
	uid_t uid;
	uid_t euid;
	uid = getuid();		/* 得到进程的实际用户ID */
	euid = geteuid();	/* 得到进程的有效用户ID */
	printf("the uid is : %d\n", uid);
	printf("the euid is : %d\n", euid);
	if(setuid(8000) == -1){ /* 改变进程的实际用户ID和有效用户ID */
		perror("fail to set uid");
		exit(1);
	}
	printf("after changing\n");
	uid = getuid();		/* 再次得到进程的实际用户ID */
	euid = geteuid();	/* 再次得到进程的有效用户ID */
	printf("the uid is : %d\n", uid);
	printf("the euid is : %d\n", euid);
	return 0;
}
