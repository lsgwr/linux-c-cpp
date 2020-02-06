/***********************************************************
 * @Description : 判断是否是输入地整数
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 19:58
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

int main() {
    int a;
    cout << "请输入一个数据：";
    cin >> a;
    cout << "状态值为：" << cin.rdstate() << endl;
    if (cin.good()) {
        cout << "输入数据的类型正确，无错误！" << endl;
    }
    if (cin.fail()) {
        cout << "输入数据类型错误！" << endl;
    }
    return 0;
}
/**
 * 第一种情况
 * 请输入一个数据：10
 * 状态值为：0
 * 输入数据的类型正确，无错误！
 *
 * 第二种情况：
 * 请输入一个数据：abcde
 * 状态值为：4
 * 输入数据类型错误！
 */
