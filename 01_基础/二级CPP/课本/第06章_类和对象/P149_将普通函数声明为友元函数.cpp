/***********************************************************
 * @Description : P149_将普通函数声明为友元函数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 23:23
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Time {
public:
    int hour, minute, sec;

    Time(int hour, int minute, int sec) : hour(hour), minute(minute), sec(sec) {}

    // 声明为Time类的友元函数,
    friend void display(Time &t);
};

// 友元函数可以直接访问类的私有成员
void display(Time &t) {
    cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}

int main() {
    Time t1(10, 13, 56);
    display(t1);
    return 0;
}