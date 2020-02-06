/***********************************************************
 * @Description : P37_读文本文件并显示在屏幕上
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 20:20
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string line;
    // 1.通过构造函数创建文件输入流
    ifstream in("a.txt");
    // 2.若文件不存在，直接返回
    if (!in) {
        cout << "文件不存在！" << endl;
        return 0;
    }
    while (getline(in, line)) {
        // 通过getline逐行读取内容
        cout << line << endl;
    }
    // 记得关闭文件
    in.close();
    return 0;
}