/***********************************************************
 * @Description : STL迭代器
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 17:48
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    cout << "请输入数据(多个数字用空格隔开)：";
    // 建立键盘输入流，并用istream_iterator枚举整型数据
    istream_iterator<int> a(cin);
    // 输入流结束迭代器
    istream_iterator<int> b;
    while (1) {
        cout << *a << endl;
        a++;
        if (a == b) {
            break;
        }
    }
    return 0;
}