/***********************************************************
 * @Description : P182_二义性测试2
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 11:09
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>

using namespace std;

class Base {
public:
    int a;

    void display() {
        cout << "Base display" << endl;
    }
};

class A : public Base {
};

class B : public Base {
};

class C : public A, public B {
public:
    void show() {
        cout << "C show" << endl;
    }
};

int main() {
    C c;
    // c.a; // 这里的a就是二义性了~
    return 0;
}
