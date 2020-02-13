/***********************************************************
 * @Description : 第06章_类和对象/P150_友元成员函数.cpp
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 23:30
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/

#include <iostream>

using namespace std;

class Shape; // 提前引用声明Shape类
class Rectangle {
private:
    int points;
    int vertexs;

public:
    Rectangle(int points, int vertexs) : points(points), vertexs(vertexs) {}

    void display(Shape &s);
};

class Shape {
private:
    int length;
    int width;
public:
    Shape(int length, int width) : length(length), width(width) {}

    // 声明Rectangle中的display()函数为友元函数
    friend void Rectangle::display(Shape &s);
};

void Rectangle::display(Shape &s) {
    cout << s.length << "--" << s.width << endl;
    cout << vertexs << "--" << points << endl;
}

int main() {
    Rectangle r1(10, 13);
    Shape s1(12, 25);
    r1.display(s1);
    return 0;
}
/**
12--25
13--10
*/