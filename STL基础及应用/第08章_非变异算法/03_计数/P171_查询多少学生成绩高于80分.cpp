/***********************************************************
 * @Description : P171_查询多少学生成绩高于80分.cpp
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 11:40
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

    bool operator==(int grade) {
        return this->grade == grade;
    }
};

class MatchExpress {
    int grade;
public:
    MatchExpress(int grade) : grade(grade) {}

    bool operator()(Student &stu) {
        return stu.grade > grade;
    }
};

int main() {
    vector<Student> vStu;
    Student s1(101, "张三", 80);
    Student s2(102, "李四", 85);
    Student s3(103, "王五", 80);
    Student s4(104, "赵六", 80);
    vStu.push_back(s1);
    vStu.push_back(s2);
    vStu.push_back(s3);
    vStu.push_back(s4);

    int nCount = count_if(vStu.begin(), vStu.end(), MatchExpress(80));
    cout << "成绩高于80分的人数为：" << nCount << endl;
    return 0;
}
/**
成绩高于80分的人数为：1
*/