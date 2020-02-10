#include <stdio.h>
//定义结构体 time_struct
struct time_struct
{
	int hour;
	int minute;
	int second;
};
int main( void )
{
	//声明一个time_struct类型的变量st_time1
	struct time_struct st_time1;
	//输出变量st_time1的值
	printf("%d,%d,%d\n", st_time1.hour, st_time1.minute, 
	st_time1.second);
	//声明一个time_struct类型的变量st_time2
	struct time_struct st_time2;
	//初始化变量st_time2
	st_time2.hour = 12;
	st_time2.minute = 10;
	st_time2.second = 18;
	//输出变量st_time的值
	printf("%d,%d,%d\n", st_time2.hour, st_time2.minute,
	st_time2.second);
	return 0;
}
