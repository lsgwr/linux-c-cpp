/***********************************************************
 * @Description : P67_算术类基本函数使用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 20:17
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <iostream>

using namespace std;

int main() {
    // 算术函数对象
    plus<int> plusObj;
    minus<int> minusObj;
    multiplies<int> mulObj;
    divides<int> divObj;
    modulus<int> modObj;
    negate<int> negObj;
    // 运用上面的对象，履行函数功能
    cout << plusObj(2, 4) << endl;
    cout << minusObj(2, 4) << endl;
    cout << mulObj(2, 4) << endl;
    cout << divObj(2, 4) << endl;
    cout << modObj(5, 3) << endl;
    cout << negObj(4) << endl;

    cout << "" << endl;
    // 以下直接以函数对象的临时对象履行函数功能
    // 语法分析：function<T>()是一个临时对象，调用operator运算符
    cout << plus<int>()(2, 4) << endl;
    cout << minus<int>()(2, 4) << endl;
    cout << multiplies<int>()(2, 4) << endl;
    cout << divides<int>()(2, 4) << endl;
    cout << modulus<int>()(5, 3) << endl;
    cout << negate<int>()(4) << endl;
    return 0;
}
/**
6
-2
8
0
2
-4

6
-2
8
0
2
-4
*/