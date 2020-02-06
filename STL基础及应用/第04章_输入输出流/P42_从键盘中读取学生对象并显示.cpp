/***********************************************************
 * @Description : P42_从键盘中读取学生对象并显示
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 21:58
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>

using namespace std;

class Student {
public:
    string name;
    string sex;
    int age;
};

istream &operator>>(istream &is, Student &stu) {
    is >> stu.name >> stu.sex >> stu.age;
    return is;
}

ostream &operator<<(ostream &os, Student &stu) {
    os << stu.name << "\t" << stu.sex << "\t" << stu.age << "\n";
    return os;
}

void f(Student &stu) {
    cout << stu;
}

int main() {
    Student stu;
    cout << "请输入学生信息(姓名 性别 年龄)：";
    cin >> stu;
    cout << "输出学生：";
    cout << stu;
    f(stu);
    return 0;
}
/**
请输入学生信息(姓名 性别 年龄)：张三 男 22
输出学生：张三	男	22
张三	男	22
*/