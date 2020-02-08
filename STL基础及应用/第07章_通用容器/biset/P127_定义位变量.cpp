/***********************************************************
 * @Description : P127_定义位变量
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 21:36
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    bitset<5> b1;  // 初始化一个至少具有5位的内存空间
    cout << "初始内存空间内容：" << b1.to_string() << endl;
    cout << "位容器空间(size)：" << b1.size() << "\t 1的个数为：" << b1.count() << endl;

    b1.set(2, true);  // 将第2位置为1
    cout << "第2位置为true后，内存空间内容" << b1.to_string() << endl;

    b1[3] = 1;
    cout << "第3位置为true后，内存空间内容" << b1.to_string() << endl;

    b1.set();
    cout << "所有位置为true后，内存空间内容" << b1.to_string() << endl;

    bitset<16> b2(65535); // 通过长整型建立位容器
    cout << "通过长整型建立位容器：" << b2.to_string() << endl;

    bitset<5> s3(string("1111101"), 2, 5);
    cout << "通过字符串建立位容器(超过初始化的大小会进行截取)：" << s3.to_string() << endl;
    return 0;
}
/**
初始内存空间内容：00000
位容器空间(size)：5	 1的个数为：0
第2位置为true后，内存空间内容00100
第3位置为true后，内存空间内容01100
所有位置为true后，内存空间内容11111
通过长整型建立位容器：1111111111111111
通过字符串建立位容器(超过初始化的大小会进行截取)：11101
*/