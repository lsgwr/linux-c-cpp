/***********************************************************
 * @Description : P87_引用与变量的关系
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/12 17:34
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

int main() {
    int a = 2;
    // 声明a的引用变量b
    int &b = a;
    // 下面a和b的调用实际都是对同一块内存单元的调用
    a *= 5;
    cout << a << "," << b << endl;
    b /= 2;
    cout << a << "," << b << endl;
    return 0;
}