#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid, ppid, uid, euid, gid, egid;
	pid = getpid();		/* 得到进程ID */
	ppid = getppid();	/* 得到父进程ID */
	uid = getuid();		/* 得到用户ID */
	euid = geteuid();	/* 得到有效用户ID */
	gid = getgid();		/* 得到组ID */
	egid = getegid();	/* 得到有效组ID */
	printf("id of current process : %u\n", pid); /* pid_t实际上是无符号整型，
													所以使用%u而不是%d */
	printf("parent id of current process : %u\n", ppid);
	printf("user id of current process : %u\n", uid);
	printf("effective user id of current process : %u\n", euid);
	printf("group id of current process : %u\n", gid);
	printf("effective group id of current process : %u\n", egid);
	return 0;
}
