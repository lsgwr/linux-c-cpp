/***********************************************************
 * @Description : STL输出迭代器
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 17:55
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    cout << "输出迭代器演示结果为：" << endl;
    // 自定义输出迭代器，用tab作为分隔符
    ostream_iterator<int> myout(cout, "\t");
    *myout = 1;
    myout++;
    *myout = 2;
    myout++;
    *myout = 3;
    return 0;
}