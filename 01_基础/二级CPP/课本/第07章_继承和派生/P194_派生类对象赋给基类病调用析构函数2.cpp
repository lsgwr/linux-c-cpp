/***********************************************************
 * @Description : P191_继承中的同名函数
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 12:16
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>
#include <string>

using namespace std;

class Person {
public:
    string name;
    char sex;
    int age;

    Person(string name, char sex, int age) : name(std::move(name)), sex(sex), age(age) {
        cout << "Person的构造函数被调用啦~" << endl;
    }


    virtual ~Person() {
        cout << "Person的析构函数被调用啦~" << endl;
    }
};

class Staff : public Person {
public:
    float wage;

    Staff(const string &name, char sex, int age, float wage) : Person(name, sex, age) {
        this->wage = wage;
        cout << "Staff的构造函数被调用啦~" << endl;
    }

     ~Staff() {
        cout << "Staff的析构函数被调用啦~" << endl;
    }

};

int main() {
    // 向上转换
    // 如果用new运算符建立临时对象，若基类中有析构函数，并且定义了一个指向该基类的指针变量。在程序用带指针参数的delete运算符撤销对象时，
    // 会发生一个情况：系统会只执行基类的构造函数，而不执行派生类的构造函数，为了执行派生类的析构函数需要给基类的析构函数加virtual
    Person *pp = new Staff("Soledad", 'f', 123, 1231.6);
    delete pp;
    return 0;
}
/**
Person的构造函数被调用啦~
Staff的构造函数被调用啦~
Staff的析构函数被调用啦~
Person的析构函数被调用啦~
 */

