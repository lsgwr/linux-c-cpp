// Time类定义 
public class Time
{
	// 小时的有效范围是0~23
	private int hour;
	// 分的有效范围是0~59
	private int minute;
	// 秒的有效范围是0~59
	private int second;
	// 默认构造函数
	public Time()
	{
		// 默认初始值为0
		setTime( 0, 0, 0);
	}
	// 重新设置时间函数，并在设置前对参数进行合法性检查
	public void setTime( int h, int m, int s )
	{
		hour = ( h >= 0 && h < 24 )? h:0;
		minute = ( m >= 0 && m < 60)? m:0;
		second = ( s >= 0 && s < 60 )? s:0;
	}
	// 对时间进行格式化，将其转化成字符串形式
	public String toString()
	{
		return String.format("%.2d:%2d:%2d", hour, minute, second);
	}
}
public class TimeTest
{
	public static void main( String args[ ] )
{
	// 声明一个Time类型的变量time1
		Time time1 = new Time();
		system.out.print("time1 is:");
		system.out.println(time1.toString());
		// 声明一个Time类型的变量time2
		Time time2 = new Time();
		time2.setTime(12, 10, 18);
		system.out.print("time2 is:");
		system.out.println(time2.toString());
	}
}
