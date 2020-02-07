/***********************************************************
 * @Description : P70_关系运算符基本函数使用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 20:42
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <iostream>

using namespace std;

int main() {
    // 以下是一些关系运算类函数对象实体
    equal_to<int> equalObj;
    not_equal_to<int> notEqualToObj;
    greater<int> greaterObj;
    greater_equal<int> greaterEqualObj;
    less<int> lessObj;
    less_equal<int> lessEqualObj;
    // 运用上述对象执行功能
    cout << equalObj(2, 4) << endl;
    cout << notEqualToObj(2, 4) << endl;
    cout << greaterObj(2, 4) << endl;
    cout << greaterEqualObj(2, 4) << endl;
    cout << lessObj(2, 4) << endl;
    cout << lessEqualObj(2, 4) << endl;
    cout << "" << endl;

    // 以下对象直接以临时对象执行函数功能
    cout << equal_to<int>()(2, 4) << endl;
    cout << not_equal_to<int>()(2, 4) << endl;
    cout << greater<int>()(2, 4) << endl;
    cout << greater_equal<int>()(2, 4) << endl;
    cout << less<int>()(2, 4) << endl;
    cout << less_equal<int>()(2, 4) << endl;
    return 0;
}
/**
0
1
0
0
1
1

0
1
0
0
1
1
*/