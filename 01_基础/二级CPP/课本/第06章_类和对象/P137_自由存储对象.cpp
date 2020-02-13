/***********************************************************
 * @Description : P137_自由存储对象
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 21:49
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Rectangle {
private:
    int edge;
    int angle;

public:
    Rectangle() {
        cout << "默认构造函数被调用啦~" << endl;
    }

    Rectangle(int edge, int angle) : edge(edge), angle(angle) {}

    virtual ~Rectangle() {
        cout << "析构函数被调用啦~" << endl;
    }

    void set(int edge, int angle) {
        this->edge = edge;
        this->angle = angle;
    }

    void draw() {
        cout << "Shape of " << angle << " and " << edge << endl;
    }
};

int main() {
    Rectangle *rect = new Rectangle(4, 4);
    rect->draw();

    Rectangle *rect1 = new Rectangle();
    rect1->set(1, 2);
    rect1->draw();

    Rectangle *rect2 = new Rectangle[2];
    rect2[0].set(2, 3);
    rect2[0].set(3, 2);
    rect2[0].draw();
    rect2[1].draw();
    delete rect;
    delete rect1;
    delete[] rect2;
    return 0;
}
/**
Shape of 4 and 4
默认构造函数被调用啦~
Shape of 2 and 1
默认构造函数被调用啦~
默认构造函数被调用啦~
Shape of 2 and 3
Shape of 0 and 0
析构函数被调用啦~
析构函数被调用啦~
析构函数被调用啦~
析构函数被调用啦~
*/