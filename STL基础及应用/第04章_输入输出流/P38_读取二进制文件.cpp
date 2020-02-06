/***********************************************************
 * @Description : P38_读取二进制文件
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 20:52
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <fstream>
#include <iostream>

using namespace std;

struct Student {
    string name;
    int grade;
};

int main() {
    ifstream in;
    in.open("b.txt");
    Student s1;
    Student s2;
    // write方法是写入二进制文件
    in.read((char *) &s1, sizeof(Student));
    in.read((char *) &s2, sizeof(Student));
    cout << s1.name << "\t" << s1.grade << endl;
    cout << s2.name << "\t" << s2.grade << endl;
    in.close();
    return 0;
}
/**
张三	80
李四	90
*/