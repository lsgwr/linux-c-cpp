#include <unistd.h>
int main(int argc, char *argv[])
{
	int i;
	for(i = 0; i < 60; i++)	/* 一个循环，每次循环时休眠 */
	{
		sleep(1);				/* 休眠一秒钟 */
	}
	return 0;
}
