/***********************************************************
 * @Description : P181_二义性测试
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 11:09
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>

using namespace std;

class Point {
private:
    int x, y;
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {
        cout << "Point的构造函数！" << endl;
    }

    void show() {
        cout << "Point show" << endl;
    }
};

class Line {
private:
    int length;
public:
    Line(int length = 0) : length(length) {
        cout << "Line 的构造函数~" << endl;
    }

    void show() {
        cout << "Line show" << endl;
    }
};

class Circle : public Point, public Line {
private:
    int radius;
public:
    Circle(int cx, int cy, int len, int r) : Line(len), Point(cx, cy), radius(radius) {
        cout << "Circle的构造函数~" << endl;
        radius = r;
    }

    void display() {
        cout << "Circle show" << endl;
    }
};

int main() {
    Circle c(3,4,5,6);
    // c.show(); // 二义性，不能确定用Point和Line哪一个的show
    c.show();
    return 0;
}
