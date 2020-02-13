/***********************************************************
 * @Description : P179_派生类的析构函数
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 10:26
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>

using namespace std;

class Base {
private:
    int valB;
public:
    Base(int x) : valB(x) {
        cout << "Base构造函数：" << valB << endl;
    }

    virtual ~Base() {
        cout << "Base析构函数：" << valB << endl;
    }
};

class Derived : public Base {
private:
    int valD;
public:
    Derived(int x = 0, int y = 0) : Base(x), valD(y) {
        cout << "Derived构造函数：" << valD << endl;
    }

    virtual ~Derived() {
        cout << "Derived析构函数：" << valD << endl;
    }
};

 int main() {
    Derived obj(2, 3);
    return 0;
}

