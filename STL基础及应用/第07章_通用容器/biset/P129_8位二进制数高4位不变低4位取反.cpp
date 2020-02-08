/***********************************************************
 * @Description : P129_8位二进制数高4位不变低4位取反
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 22:03
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    bitset<8> b(string("11011101"));
    cout << "原位容器b：" << b.to_string() << endl;
    for (int i = 0; i < 4; ++i) {
        b.flip(i);
    }
    cout << "低4位反转后的b：" << b.to_string() << endl;
    return 0;
}
/**
原位容器b：11011101
低4位反转后的b：11010010
*/