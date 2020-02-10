/***********************************************************
 * @Description : P44_从文本中读取每个学生的各科成绩_方法1
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 22:10
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
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

int main() {
    ifstream in("data.txt");
    Student s;
    while (!in.eof()) {
        in >>s;
        cout << s << endl;
    }
    return 0;
}