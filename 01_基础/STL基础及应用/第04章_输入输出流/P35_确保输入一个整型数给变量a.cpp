/***********************************************************
 * @Description : P35_确保输入一个整型数给变量a
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 20:10
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

int main() {
    int a;
    while (1) {
        cin >> a;
        if (cin.fail()) {
            cout << "输入有错，请重新输入！" << endl;
            cin.clear(); // 清空状态标志位
            cin.get(); // 清空流缓冲区
        } else {
            cout << a << endl;
            break;
        }
    }
    return 0;
}
/**
a
输入有错，请重新输入！
sdsf
输入有错，请重新输入！
输入有错，请重新输入！
输入有错，请重新输入！
输入有错，请重新输入！
1
1
 */