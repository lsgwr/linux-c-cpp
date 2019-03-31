#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



int main(void)
{
	pid_t pid;
	pid_t ppid;
	uid_t uid;	
	gid_t gid;	


	pid = getpid();
	
	printf("pid = %d\n", pid);


	ppid = getppid();
	printf("ppid = %d\n", ppid);	


	uid = getuid();
	printf("uid = %d\n", uid);

	gid = getgid();
	printf("gid = %d\n", gid);

	while(1); 
	
	
	
	return 0;
}
