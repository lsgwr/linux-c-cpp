/***********************************************************
 * @Description : P202_学生信息筛选
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 19:03
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

class Student {
public:
    string no;   // 学号
    string name; // 姓名
    int chinese; // 语文
    int math;    // 数学

    Student(string no, string name, int chinese, int math) :
            no(std::move(no)), name(std::move(name)), chinese(chinese), math(math) {}

    bool operator<(const int &total) const {
        return (chinese + math) < total;
    }
};

bool MyCompare(const Student &stu) {
    // 上面重写了operator
    return stu < 150;
}

ostream &operator<<(ostream &os, const Student &stu) {
    os << stu.name << "\t" << stu.chinese << "\t" << stu.math;
    return os;
}

int main() {
    Student s1("张三", "1001", 60, 70);
    Student s2("李四", "1002", 70, 80);
    Student s3("王五", "1003", 75, 85);
    Student s4("赵六", "1004", 68, 78);
    Student s5("宋七", "1005", 86, 76);
    Student s6("刘八", "1006", 30, 80);

    vector<Student> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    v.push_back(s4);
    v.push_back(s5);
    v.push_back(s6);
    ofstream out("stud.dat");
    remove_copy_if(v.begin(), v.end(), ostream_iterator<Student>(out, "\n"), MyCompare);
    out.close();
    return 0;
}
/**
1002	70	80
1003	75	85
1005	86	76
*/