//头文件包含

#include <iostream>

using namespace std;

//Time类的定义

class Time

{

public:

	// 默认构造函数

	Time();

	// 设置时间的函数

	void SetTime( int, int, int );

	// 格式化输出时间

	void DisplayTimeMilitary();

private:

	// 小时的有效范围是0~23

	int hour;

	// 分的有效范围是0~59

	int minute;

	// 秒的有效范围是0~59

	int second;

};

// 构造函数

// 默认值均为0

Time::Time()

{

	hour = 0;

	minute = 0;

	second = 0;

}

// 该函数用来重新设置时间

// 设置时间前对参数进行合法性检查，如果参数无效，则使用默认值

void Time::SetTime( int h, int m, int s )

{

	this->hour = ( h >= 0 && h < 24 )? h:0;

	this->minute = ( m >= 0 && h < 60 )? m:0;

	this->second = ( s >= 0 && s < 60 )? s:0;

}

// 格式化输出时间，其格式为hh:mm:ss

void Time::DisplayTimeMilitary()

{

	cout<<( this->hour < 10 ? "0":"")<< this->hour<<":"

		<< (this->minute < 10 ? "0":"")<< this->minute

		<< (this->minute < 10 ? "0":"")<< this->second<< endl;

}

int main()

{

	Time t1;

	cout<<"t1 is:";

	t1.DisplayTimeMilitary();

	Time t2;

	t2.SetTime( 12, 10, 18 );

	cout<<"t2 is:";

	t2.DisplayTimeMilitary();

	return 0;

}