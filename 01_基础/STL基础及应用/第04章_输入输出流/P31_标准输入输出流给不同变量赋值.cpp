/***********************************************************
 * @Description : P31_标准输入输出流给不同变量赋值
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 19:30
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

int main() {
    int i;
    float f;
    char str[20];

    cin >> i;
    cin >> f;
    cin >> str;

    cout << "i=" << i << endl;
    cout << "f=" << f << endl;
    cout << "str=" << str << endl;
    return 0;
}
/**
10
2.3
dsdf
i=10
f=2.3
str=dsdf
 */
