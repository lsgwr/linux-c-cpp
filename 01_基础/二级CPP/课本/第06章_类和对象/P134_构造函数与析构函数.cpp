/***********************************************************
 * @Description : 构造函数与析构函数
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/12 19:24
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Shape {
private:
    int edge;
    int angle;

public:
    Shape(int edge, int angle) : edge(edge), angle(angle) {}

    Shape() {}

    virtual ~Shape() {
        cout << edge << endl;
        cout << angle << endl;
        cout << "~Shape call" << endl;
    }


    int getEdge() const {
        return edge;
    }

    void setEdge(int edge) {
        Shape::edge = edge;
    }

    int getAngle() const {
        return angle;
    }

    void setAngle(int angle) {
        Shape::angle = angle;
    }

    void draw() {
        cout << "Shape of " << angle << " and " << edge << endl;
    }

};

int main() {
    auto *shape = new Shape();
    shape->setEdge(4);
    shape->setAngle(4);
    shape->draw();

    auto *shape1 = new Shape(5, 5);
    shape1->draw();
    delete shape;
    delete shape1;
    return 0;
}
/**
Shape of 4 and 4
Shape of 5 and 5
4
4
~Shape call
5
5
~Shape call
*/