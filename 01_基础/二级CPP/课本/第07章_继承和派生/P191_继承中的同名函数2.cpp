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

    virtual void show() {
        cout << "name:" << name << endl;
        cout << "age:" << age << endl;
        cout << "sex:" << sex << endl;
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
    Staff staff("Soledad", 'm', 24, 122234);
    Person person("Soledad2", 'f', 34);

    Person *pp;
    // 向上转型
    pp = &staff;
    pp->show();
    pp = &person;
    pp->show();
    return 0;
}
/**
Person的构造函数被调用啦~
Staff的构造函数被调用啦~
Person的构造函数被调用啦~
name:Soledad
age:24
sex:m
wage:122234
name:Soledad2
age:34
sex:f
Person的析构函数被调用啦~
Staff的析构函数被调用啦~
Person的析构函数被调用啦~
 */

