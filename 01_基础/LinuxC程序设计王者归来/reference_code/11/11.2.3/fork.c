#include <unistd.h>
int main()
{
	while(1)
		fork(); /* 不断地创建子进程，使系统中进程溢满 */
	return 0;
}
