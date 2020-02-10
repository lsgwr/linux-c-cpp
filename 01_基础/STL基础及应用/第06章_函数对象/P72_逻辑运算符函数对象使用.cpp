/***********************************************************
 * @Description : P72_逻辑运算符函数对象使用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 21:31
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <functional>

using namespace std;

int main() {
    // 产生一些函数对象实体
    logical_and<int> andObj;
    logical_or<int> orObj;
    logical_not<int> notObj;

    // 运用上述对象执行函数功能
    cout << andObj(true, true) << endl;
    cout << orObj(true, false) << endl;
    cout << notObj(true) << endl;

    // 利用临时对象执行函数功能
    cout << logical_and<int>()(3 < 5, 6 < 9) << endl;
    cout << logical_or<int>()(3 < 5, 6 > 9) << endl;
    cout << logical_not<int>()(3 < 5) << endl;
    return 0;
}
/**
1
1
0
1
1
0
*/