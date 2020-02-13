/***********************************************************
 * @Description : P185_虚基类构造函数_析构函数_成员变量
 *
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 11:33
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>
#include <utility>

using namespace std;

class Person {
public:
    string name;
    char sex;
    int age;

    Person(string name, char sex, int age) : name(std::move(name)), sex(sex), age(age) {
        cout << "Person的构造器碑调用啦~" << endl;
    }

    virtual ~Person() {
        cout << "Person的析构函数碑调用啦~" << endl;
    }
};


class Manager : virtual public Person {
public:
    string power;

    Manager(const string &name, char sex, int age, string power) : Person(name, sex, age) {
        cout << "Manager的构造函数被调用啦~" << endl;
        this->power = std::move(power);
    }

    virtual ~Manager() {
        cout << "Manager的构造函数被调用啦~" << endl;
    }
};

class Employee : virtual public Person {
public:
    int workdays;

    Employee(const string &name, char sex, int age, int workdays) : Person(name, sex, age) {
        this->workdays = workdays;
        cout << "Employee的构造函数被调用啦~" << endl;
    }

    virtual ~Employee() {
        cout << "Employee的析构函数被调用啦~" << endl;
    }
};

class Staff : public Manager, public Employee {
public:
    Staff(const string &name, char sex, int age, const string &power, int workdays, int wage) :
            Person(name, sex, age), Manager(name, sex, age, power), Employee(name, sex, age, workdays) {
        this->wage = wage;
        cout << "Staff的构造函数被调用啦~" << endl;
    }

    virtual ~Staff() {
        cout << "Staff的析构函数被调用啦~" << endl;
    }

    void show() {
        cout << "name:" << name << endl;
        cout << "age:" << age << endl;
        cout << "power:" << power << endl;
        cout << "workdays:" << workdays << endl;
        cout << "wage" << wage << endl;
    }

    int wage;
};

int main() {
    Staff staff("Scoledad", 'm', 24, "large", 365, 122234);
    staff.show();
    return 0;
}
/**
Person的构造器碑调用啦~
Manager的构造函数被调用啦~
Employee的构造函数被调用啦~
Staff的构造函数被调用啦~
name:Scoledad
age:24
power:large
workdays:365
wage122234
Staff的析构函数被调用啦~
Employee的析构函数被调用啦~
Manager的构造函数被调用啦~
Person的析构函数碑调用啦~
 */
