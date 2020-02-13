/***********************************************************
 * @Description : P143_成员函数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 22:59
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Point {
public:
    int x, y;

    Point(int x, int y);

    static int count;

    static void show() {
        cout << "类的静态函数被调用啦~" << endl;
    }
};

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

// 静态成员变量的初始化一般在类体外进行
int Point::count = 100;

int main() {
    Point a(15,10), b(20, 20);
    a.show();
    b.show();
    Point::show();
    return 0;
}
/**
类的静态函数被调用啦~
类的静态函数被调用啦~
类的静态函数被调用啦~
*/