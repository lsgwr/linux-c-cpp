/***********************************************************
 * @Description : P32_标准输入给不同类型变量赋值的不足示例
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 19:41
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

int main() {
    int i;
    char str[20];

    cout << "请输入一个整型数及一个字符串：" << endl;
    cin >> i >> str;

    cout << "i=" << i << endl;
    cout << "str=" << str << endl;
    return 0;
}