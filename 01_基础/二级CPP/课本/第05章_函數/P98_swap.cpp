/***********************************************************
 * @Description : 基于引用的swap函数
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/12 17:56
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

int main() {
    int a = 3, b = 4;
    swap(a, b);
    cout << a << ", " << b << endl;
    cout << a * a + b << endl;
    return 0;
}
