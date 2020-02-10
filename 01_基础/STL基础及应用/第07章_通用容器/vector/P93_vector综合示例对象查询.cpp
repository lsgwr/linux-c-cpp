/***********************************************************
 * @Description : P93_vector综合示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 12:49
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    string no;   // 学号
    string name; // 姓名
    string sex;  // 性别
    string date; // 年龄

public:
    Student(string no, string name, string sex, string date) :
            no(std::move(no)), name(std::move(name)), sex(std::move(sex)), date(std::move(date)) {}

    void display() {
        cout << no << "\t" << name << "\t" << sex << "\t" << date << endl;
    }
};

// 学生集合
class StudCollect {
    vector<Student> vStu;
public:
    void add(Student &s) {
        vStu.push_back(s);
    }

    /**
     * 根据学号查找学生对象
     * @param no
     * @return 查找到的学生对象
     */
    Student *find(string no) {
        bool bFind = false;
        for (auto &stu : vStu) {
            if (stu.no == no) {
                return &stu;
            }
        }
        return nullptr;
    }
};

int main() {
    Student s1("1001", "张三", "男", "1985-10-10");
    Student s2("1002", "李四", "男", "1984-06-10");
    Student s3("1003", "王五", "男", "1985-11-15");
    StudCollect s;
    s.add(s1);
    s.add(s2);
    s.add(s3);
    Student *ps = s.find("1002");
    if (ps) {
        ps->display();
    }
    return 0;
}