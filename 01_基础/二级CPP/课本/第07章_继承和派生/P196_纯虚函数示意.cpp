/***********************************************************
 * @Description : P196_纯虚函数示意
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 14:27
 * @email       : liangshanguang2@gmail.com
***********************************************************/

#include <iostream>

using namespace std;

class Person {
public:
    string name;
    char sex;
    int age;

    Person(string name, char sex, int age) : name(std::move(name)), sex(sex), age(age) {
        cout << "Person的构造函数被调用啦~" << endl;
    }

    virtual void show() = 0;

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

    virtual ~Staff() {
        cout << "Staff的析构函数被调用啦~" << endl;
    }

    void show() {
        cout << "name:" << name << endl;
        cout << "age:" << age << endl;
        cout << "sex:" << sex << endl;
        cout << "wage:" << wage << endl;
    }
};

int main() {
    Person *pp = new Staff("soledad", 'f', 123, 1231.6);
    pp->show();
    delete pp;
    return 0;
}
/**
Person的构造函数被调用啦~
Staff的构造函数被调用啦~
name:soledad
age:123
sex:f
wage:1231.6
Staff的析构函数被调用啦~
Person的析构函数被调用啦~
*/