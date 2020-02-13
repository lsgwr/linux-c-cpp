/***********************************************************
 * @Description : P146_常成员函数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 23:11
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/

#include <iostream>

using namespace std;

class A {
private:
    int w, h;

public:
    int getValue() const;

    int getValue();

    A(int w, int h) : w(w), h(h) {}

    A() {}
};

int A::getValue() {
    cout << "没有const的成员函数" << endl;
    return w * h;
}

int A::getValue() const {
    cout << "带const的成员函数" << endl;
    return w * h;
}

int main() {
    A const a(3,4);
    A c(2,6);
    cout << a.getValue() << endl;
    cout << c.getValue() << endl;
    return 0;
}
/**
带const的成员函数
12
没有const的成员函数
12
*/