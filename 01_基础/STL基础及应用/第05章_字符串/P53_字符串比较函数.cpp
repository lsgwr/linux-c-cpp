/***********************************************************
 * @Description : P53_字符串比较函数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 16:44
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s1 = "this";
    string s2 = "that";
    int cmp = s1 < s2;
    cout << cmp << endl;
    return 0;
}

