/***********************************************************
 * @Description : P44_从文本中读取每个学生的各科成绩_方法1
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 22:10
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ifstream in("data.txt");

    string strText;
    string name;
    // 语文
    int chinese = 0;
    // 数学
    int math = 0;
    // 英语
    int english = 0;
    // 总分
    int total;
    while (!in.eof()) {
        getline(in, strText); // 读取每行文本保存到字符串中
        istringstream inf(strText); // 把该文本串封装成字符串输入流对象
        inf >> name >> chinese >> math >> english; // 解析字符串给各个变量
        total = chinese + math + english;
        cout << "姓名：" << name << "\t语文：" << chinese << "\t数学：" << math << "\t英语：" << english << "\t总分:" << total << endl;
    }
    return 0;
}