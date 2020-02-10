/***********************************************************
 * @Description : P225_求成绩最好的3位同学
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 22:21
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

class Student {
public:
    int no;   // 学号
    string name; // 姓名
    int grade; // 成绩

    Student(int no, string name, int grade) : no(no), name(std::move(name)), grade(grade) {}

    /**
     * 降序排列需要重载的操作符
     */
    bool operator>(const Student &stu) const {
        return grade > stu.grade;
    }

    /**
     * 升序排列需要重载的操作符
     */
    bool operator<(const Student &stu) const {
        return grade < stu.grade;
    }
};

int main() {
    Student s1(101, "张三", 90);
    Student s2(102, "李四", 80);
    Student s3(103, "王五", 85);
    Student s4(104, "赵六", 65);
    Student s5(105, "孙八", 96);
    Student s6(106, "刘九", 85);
    Student s7(107, "韩十", 83);
    Student s8(108, "哈文", 62);

    vector<Student> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    v.push_back(s4);
    v.push_back(s5);
    v.push_back(s6);
    v.push_back(s7);
    v.push_back(s8);

    vector<Student> vResult(3); // 保存最好的3个学生的向量
    partial_sort_copy(v.begin(), v.end(), vResult.begin(), vResult.end(), greater<Student>());
    for (auto &stu : vResult) {
        cout << stu.no << "\t" << stu.name << "\t" << stu.grade << endl;
    }
    return 0;
}
/**
105	孙八	96
101	张三	90
103	王五	85
*/