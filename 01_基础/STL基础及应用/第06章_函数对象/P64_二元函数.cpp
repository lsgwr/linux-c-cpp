/***********************************************************
 * @Description : P64_二元函数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 19:56
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

class Student {
public:
    string name;
    int grade;

public:
    Student(const string &name, int grade) : name(name), grade(grade) {}

    bool operator<(const Student &stu) const {
        return grade < stu.grade;
    }
};

ostream &operator<<(ostream &os, const Student &stu) {
    os << stu.name << "\t" << stu.grade << "\n";
    return os;
}

// 自定义比较器
template<class _inPara1, class _inPara2>
class comparator : public binary_function<_inPara1, _inPara2, bool> {
public:
    bool operator()(_inPara1 in1, _inPara2 in2) {
        return in1 < in2;
    }
};

int main() {
    Student s1("张三", 60);
    Student s2("李四", 80);
    Student s3("王五", 70);
    Student s4("赵六", 90);

    vector<Student> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    v.push_back(s4);
    // 按照自定义的比较器进行排序
    sort(v.begin(), v.end(), comparator<const Student &, const Student &>());
    // 升序结果输出
    copy(v.begin(), v.end(), ostream_iterator<Student>(cout, ""));
    return 0;
}