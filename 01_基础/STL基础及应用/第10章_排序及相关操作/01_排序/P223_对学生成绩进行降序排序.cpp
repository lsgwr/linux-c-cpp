/***********************************************************
 * @Description : P223_对学生成绩进行排序
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 21:50
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

    bool operator<(const Student &stu) const {
        return grade < stu.grade;
    }
};

ostream &operator<<(ostream &os, const Student &stu) {
    os << stu.no << "\t" << stu.name << "\t" << stu.grade;
    return os;
}

bool myDescend(Student &s1, Student &s2) {
    return s1.grade > s2.grade;
}

int main() {
    Student s1(101, "张三", 90);
    Student s2(102, "李四", 80);
    Student s3(103, "王五", 85);
    Student s4(104, "赵六", 65);

    vector<Student> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    v.push_back(s4);

    sort(v.begin(), v.end(), myDescend);
    cout << "升序排序地结果是：" << endl;
    cout << "学号\t" << "姓名\t" << "成绩" << endl;
    copy(v.begin(), v.end(), ostream_iterator<Student>(cout, "\n"));
    return 0;
}
/**
升序排序地结果是：
学号	姓名	成绩
101	张三	90
103	王五	85
102	李四	80
104	赵六	65
*/