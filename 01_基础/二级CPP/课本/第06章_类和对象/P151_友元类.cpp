/***********************************************************
 * @Description : 友元类
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 23:44
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
    // friend void Rectangle::display(Shape &s);

    // 把上面的友元函数改成友元类，一样能访问私有成员
    friend Rectangle;
};

void Rectangle::display(Shape &s) {
    cout << s.length << "--" << s.width << endl;
    cout << vertexs << "--" << points << endl;
}

int main(){
    Rectangle r1(10, 13);
    Shape s1(12, 25);
    r1.display(s1);
    return 0;
}
/**
12--25
13--10
*/