/***********************************************************
 * @Description : P183_虚基类解决二义性的问题
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 11:25
 * @email       : liangshanguang2@gmail.com
***********************************************************/

#include <iostream>

using namespace std;

class Base {
public:
    int a;

    void display() {
        cout << "" << endl;
    }
};

// 声明A是类Base的公共派生类，Base是A的虚基类
class A : virtual public Base {

};

// 生命B是类Base的公共怕派生类，Base是B的虚基类
class B : virtual public Base {

};

class C : public A, public B {
public:
    void show() {
        cout << "C show" << endl;
    }
};

int main() {

    return 0;
}