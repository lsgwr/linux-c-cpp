#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main( void )
{
	time_t cur_time;						/* 存储当前时间的变量 */
	if ((cur_time = time (NULL)) == -1 ){	/*得到当前的系统时间*/
		perror ("time");
		exit (1);
	}
	printf ("the current time is : %d \n", (int)cur_time); /* 输出当前时间 */
	exit(0);
}
