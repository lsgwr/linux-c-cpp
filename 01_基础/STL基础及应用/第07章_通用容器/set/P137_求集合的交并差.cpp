/***********************************************************
 * @Description : P137_求集合的交并差
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 22:50
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <set>
#include <utility>

using namespace std;

class Student {
private:
    string no;   // 学号
    string name; // 姓名

public:
    Student(string no, string name) : no(std::move(no)), name(std::move(name)) {}

    /**
     * 重载比较符，按照升序排列
     */
    bool operator<(const Student &stu) const {
        int mark = no.compare(stu.no);
        return mark < 0;
    }

    const string &getNo() const {
        return no;
    }

    const string &getName() const {
        return name;
    }
};

/**
 * 为Student对象标准输出做准备
 * @param os 输出流
 * @param stu 实例对象
 * @return
 */
ostream &operator<<(ostream &os, const Student &stu) {
    os << stu.getNo() << "\t" << stu.getName();
    return os;
}

