/***********************************************************
 * @Description : P142_引用静态数据成员
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 22:10
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Point {
public:
    int x, y;

    Point(int x, int y);

    static int count;
};

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

// 静态成员变量的初始化一般在类体外进行
int Point::count = 100;

int main() {
    Point a(15, 20), b(20, 30);
    cout << a.count << endl;
    cout << b.count << endl;
    cout << Point::count << endl;
    return 0;
}
/**
 * 如下可以看到：实例变量和类变量里面的count都是相等的
100
100
100
*/