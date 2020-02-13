/***********************************************************
 * @Description : 派生类的定义和组成
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 9:10
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Point {
// 不显示地声明默认是private
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    int get() {
        return x + y;
    }
};

class Circle : public Point {
    int radius;

public:
    // 继承父类的构造函数
    Circle(int cx, int cy,int radius) :Point(cx, cy){
        this->radius = radius;
    }

    int get(){
        return Point::get() +radius;
    }
};

int main() {
    Circle c(3,4,5);
    cout << c.get() << endl; // 12
    return 0;
}

