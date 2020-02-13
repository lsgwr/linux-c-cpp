/***********************************************************
 * @Description : P173_派生类的构造函数
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 9:56
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Point1 {
    int x1, y1;
public:
    Point1(int x1, int y1) : x1(x1), y1(y1) {
        cout << "Point1的构造函数~" << endl;
    }

    void show1() {
        cout << "x1:" << x1 << "\ty1:" << y1 << endl;
    }
};

class Point2 {
    int x2, y2;
public:
    Point2(int x2, int y2) : x2(x2), y2(y2) {
        cout << "Point2的构造函数~" << endl;
    }

    void show2() {
        cout << "x2:" << x2 << "\ty2:" << y2 << endl;
    }
};

class Circle : public Point1, public Point2 {
private:
    int radius;
public:
    Circle(int x1, int y1, int x2, int y2, int radius) : Point1(x1, y1), Point2(x2, y2) {
        cout << "Circle的构造函数~" << endl;
        this->radius = radius;
    }

    void show() {
        show1();
        show2();
        cout << "radius = " << radius << endl;
    }
};

int main() {
    Circle c1(3,4,5,6,7);
    c1.show();
    Circle c2(30,40,50,60,70);
    c2.show();
    return 0;
}
/**
Point1的构造函数~
Point2的构造函数~
Circle的构造函数~
x1:3	y1:4
x2:5	y2:6
radius = 7
Point1的构造函数~
Point2的构造函数~
Circle的构造函数~
x1:30	y1:40
x2:50	y2:60
radius = 70
 */

