/***********************************************************
 * @Description : P128_位操作函数示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 21:49
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    bitset<5> b1(string("01011"));
    bitset<5> b2(string("10010"));
    cout << "b1:" << b1.to_string() << endl;
    cout << "b2:" << b2.to_string() << endl;

    b1 &= b2; // 两个位与
    cout << "b1&b2=" << b1.to_string() << endl;

    bitset<5> b3(string("01011"));
    bitset<5> b4(string("10010"));
    bitset<5> b5 = b3 & b4;
    cout << "b3：" << b3.to_string() << endl;
    cout << "b4：" << b4.to_string() << endl;
    cout << "b5：" << b5.to_string() << endl;
    cout << "原b3：" << b3.to_string() << endl;
    return 0;
}
/**
b1:01011
b2:10010
b1&b2=00010
b3：01011
b4：10010
b5：00010
原b3：01011
*/