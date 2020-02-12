/***********************************************************
 * @Description : 对象的成员
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/12 19:03
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
class Time {
public:
    int hour;
    int minute;
    int sec;

    void setTime(int hour, int minute, int sec) {
        // this是this指针的，指针用->
        this->hour = hour;
        this->minute = minute;
        this->sec = sec;
    }
};

int main() {
    Time time1;
    time1.hour = 7;
    time1.minute = 10;
    time1.sec = 40;
    time1.setTime(time1.hour, time1.minute, time1.sec);

    // 引用
    Time &time2 = time1;
    time2.minute = 20;

    // 指针
    Time *time3 = &time1;
    time3->minute = 30;
    time3->hour = 10;
    (*time3).hour = 12;
    (*time3).minute = 34;
    (*time3).sec = 45;
    return 0;
}
