/***********************************************************
 * @Description : P228_求第3好成绩的学生
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 23:15
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

    nth_element(v.begin(), v.begin()+2, v.end(), greater<Student>());
    auto it = v.begin()+2;
    cout << "第3好成绩的学生信息是：" << endl;
    cout << "学号\t" << "姓名\t" << "成绩" << endl;
    cout << (*it).no << "\t" << (*it).name << "\t" << (*it).grade << endl;
    return 0;
}
/**
第3好成绩的学生信息是：
学号	姓名	成绩
106	刘九	85
*/