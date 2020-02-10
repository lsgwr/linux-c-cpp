#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
int main(void)
{
	fd_set fdset;
	FD_ZERO(&fdset); /* 清空fdset */
	FD_SET(STDOUT_FILENO, &fdset); /* 设置stdout所对应的位 */
	if(FD_ISSET(STDOUT_FILENO, &fdset) != 0) /* 测试该位 */
		printf("stdout has been setted\n");
	else
		printf("stdout has not been setted\n");
	FD_CLR(STDOUT_FILENO, &fdset); /* 清空stdout所对应的位 */
	if(FD_ISSET(STDOUT_FILENO, &fdset) != 0) /* 在此测试该位 */
		printf("stdout has been setted\n");
	else
		printf("stdout has not been setted\n");
	return 0;
}
