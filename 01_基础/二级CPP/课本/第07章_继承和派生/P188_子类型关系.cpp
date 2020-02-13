/***********************************************************
 * @Description : 子类型关秀
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 12:01
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Person {
public:
    string name;
    char sex;
    int age;

    Person(string name, char sex, int age) : name(std::move(name)), sex(sex), age(age) {
        cout << "Person的构造函数被调用啦~" << endl;
    }

    void show() {
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

void sayUrInfo(Person &p) {
    p.show();
}

int main() {
    Staff staff("Soledad", 'm', 24, 122234);
    sayUrInfo(staff); // staff作为Person的子类，是可以传入地，会被向上转型成Person类型
    return 0;
}
/**
Person的构造函数被调用啦~
Staff的构造函数被调用啦~
name:Soledad
age:24
sex:m
Staff的析构函数被调用啦~
Person的析构函数被调用啦~
 */

