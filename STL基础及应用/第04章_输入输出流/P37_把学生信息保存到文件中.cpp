/***********************************************************
 * @Description : P37_把学生信息保存到文件中
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 20:38
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>

using namespace std;

struct Student {
    string name;
    int grade;
};

int main() {
    ofstream out;
    out.open("b.txt");
    Student s1 = {"张三", 80};
    Student s2 = {"李四", 90};
    out << s1.name << "\t" << s1.grade << endl;
    out << s2.name << "\t" << s2.grade << endl;
    out.close();
    return 0;
}