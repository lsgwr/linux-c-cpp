/***********************************************************
 * @Description : P78_学生成绩输出
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 23:28
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

class Student {
public:
    string name;
    int grade;

public:
    Student(const string &name, int grade) : name(name), grade(grade) {}
};

class StudIndex : public binary_function<int, int, bool> {
    vector<Student> &vStud; // 学生对象集合

public:
    StudIndex(vector<Student> &vStud) : vStud(vStud) {}

    bool operator()(int a, int b) {
        return vStud.at(a).grade < vStud.at(b).grade;
    }
};

int main() {
    Student s1("1001", 70);
    Student s2("1001", 60);
    Student s3("1001", 80);
    Student s4("1001", 64);
    vector<Student> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    v.push_back(s4);

    vector<int> vIndex; // 四个学生的初始索引号
    vIndex.push_back(0);
    vIndex.push_back(1);
    vIndex.push_back(2);
    vIndex.push_back(3);
    sort(vIndex.begin(), vIndex.end(), StudIndex(v));
    copy(vIndex.begin(), vIndex.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
/**
 * 1 3 0 2
 */
