/***********************************************************
 * @Description : P38_write写二进制文件
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 20:46
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
    // write方法是写入二进制文件
    out.write((const char *) &s1, sizeof(Student));
    out.write((const char *) &s2, sizeof(Student));
    out.close();
    return 0;
}