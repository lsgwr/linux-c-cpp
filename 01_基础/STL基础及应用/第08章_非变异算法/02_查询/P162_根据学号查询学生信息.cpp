/***********************************************************
 * @Description : P162_根据学号查询学生信息
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 11:03
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    int no;   // 学号
    string name; // 姓名

    Student(int no, string name) : no(no), name(std::move(name)) {}

    bool operator==(int no) {
        return this->no == no;
    }
};

int main() {
    vector<Student> vStu;
    Student s1(101, "张三");
    Student s2(102, "李四");
    Student s3(103, "王五");
    Student s4(104, "赵六");
    vStu.push_back(s1);
    vStu.push_back(s2);
    vStu.push_back(s3);
    vStu.push_back(s4);

    int noFind = 102;
    auto itFind = find(vStu.begin(), vStu.end(), noFind);
    if (itFind != vStu.end()) {
        cout << (*itFind).no << ":" << (*itFind).name << endl;
    }
    return 0;
}