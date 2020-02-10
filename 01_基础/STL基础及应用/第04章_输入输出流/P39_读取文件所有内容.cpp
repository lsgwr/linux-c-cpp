/***********************************************************
 * @Description : P39_读取文件所有内容
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 21:04
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("a.txt");
    if (fin.is_open()) {
        cout << fin.rdbuf() << endl;
    }
    fin.close()
    return 0;
}