/***********************************************************
 * @Description : P77_综合案例_求圆和长方形的面积
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 23:09
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 在基类中定义求面积的多态虚函数
class Shape {
public:
    virtual bool showArea() = 0;
};

class Circle : public Shape {
    /**
     * 半径
     */
    float r;

public:
    Circle(float r) : r(r) {}

    /**
     * 重载多态虚函数
     */
    bool showArea() override {
        cout << 3.14f * r * r << endl;
        return true;
    }
};

class Rectangle : public Shape {
    float width;
    float height;
public:
    Rectangle(float width, float height) : width(width), height(height) {}

    /**
     * 重载多态虚拟函数
     */
    bool showArea() override {
        cout << width * height << endl;
        return true;
    }
};

// 各种形状的指针集合类
class AreaCollect {
    vector<Shape *> v;

public:
    /**
     * 添加形状对象指针函数
     * @param pShape 对象指针
     */
    bool add(Shape *pShape) {
        v.push_back(pShape);
        return true;
    }

    /**
     * 显示各个形状
     */
    bool showEachArea() {
        for_each(v.begin(), v.end(), mem_fun(&Shape::showArea));
        return true;
    }
};

int main() {
    AreaCollect container;
    Shape *pObj1 = new Circle(10.0f);
    Shape *pObj2 = new Rectangle(10.0f, 20.0f);
    container.add(pObj1);
    container.add(pObj2);
    container.showEachArea();
    return 0;
}