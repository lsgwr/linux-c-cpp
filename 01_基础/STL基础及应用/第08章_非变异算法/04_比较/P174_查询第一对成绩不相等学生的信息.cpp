/***********************************************************
 * @Description : P174_查询第一对成绩不相等学生的信息
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 11:57
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Student {
public:
    int no;   // 学号
    string name; // 姓名
    int grade; // 成绩

    Student(int no, string name, int grade) : no(no), name(std::move(name)), grade(grade) {}

    bool operator==(Student &stu) {
        return this->grade == stu.grade;
    }
};

int main() {
    vector<Student> vStu1;
    Student s1(101, "张三", 90);
    Student s2(102, "李四", 80);
    Student s3(103, "王五", 70);
    vStu1.push_back(s1);
    vStu1.push_back(s2);
    vStu1.push_back(s3);

    vector<Student> vStu2;
    Student s4(104, "赵六", 90);
    Student s5(105, "孙七", 80);
    Student s6(106, "刘八", 75);
    vStu2.push_back(s4);
    vStu2.push_back(s5);
    vStu2.push_back(s6);
    typedef vector<Student>::iterator it;
    cout << "查询第一对成绩不相等的学生的信息" << endl;
    pair<it, it> result = mismatch(vStu1.begin(), vStu1.end(), vStu2.begin());

    // 取第一个不同的索引对应的两个数组的元素
    Student &stu1 = *result.first;
    Student &stu2 = *result.second;

    cout << "学号：" << stu1.no << "\t姓名：" << stu1.name << "\t成绩：" << stu1.grade << endl;
    cout << "学号：" << stu2.no << "\t姓名：" << stu2.name << "\t成绩：" << stu2.grade << endl;
    return 0;
}
/**
查询第一对成绩不相等的学生的信息
学号：103	姓名：王五	成绩：70
学号：106	姓名：刘八	成绩：75
*/