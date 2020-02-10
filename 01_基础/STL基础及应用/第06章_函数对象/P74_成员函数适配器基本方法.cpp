/***********************************************************
 * @Description : P74_成员函数适配器基本方法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 22:08
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

class Student {
    string no; // 学号
    string name; // 姓名

public:
    Student(string no, string name) : no(move(no)), name(move(name)) {}

    /**
     * 学生信息显示函数
     */
    bool show() {
        cout << no << ":" << name << endl;
        return true;
    }
};

int main() {
    // 针对对象
    Student s1("1001", "张三");
    Student s2("1002", "李四");
    vector<Student> v;
    v.push_back(s1);
    v.push_back(s2);
    for_each(v.begin(), v.end(), mem_fun_ref(&Student::show));

    cout << "" << endl;

    // 针对对象引用
    Student *ps1 = new Student("1003", "王五");
    Student *ps2 = new Student("1004", "赵六");
    vector<Student *> pv;
    pv.push_back(ps1);
    pv.push_back(ps2);
    for_each(pv.begin(), pv.end(), mem_fun(&Student::show));
    return 0;
}
/**
1001:张三
1002:李四

1003:王五
1004:赵六
*/