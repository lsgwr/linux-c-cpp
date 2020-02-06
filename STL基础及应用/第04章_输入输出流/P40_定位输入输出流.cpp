/***********************************************************
 * @Description : P40_定位输入输出流,先读后写，都是用一个fstream
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 21:34
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    fstream in_out;
    in_out.open("my.txt", ios::in | ios::out | ios::trunc);
    in_out.write("Hello", 5);

    in_out.seekg(0, ios::beg); // 移动到文件头
    cout << in_out.rdbuf() << endl; // 从文件头开始读取所有内容
    in_out.close();
    return 0;
}
/**
 * Hello
 */
