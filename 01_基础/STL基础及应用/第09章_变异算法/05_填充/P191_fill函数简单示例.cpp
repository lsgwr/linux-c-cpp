/***********************************************************
 * @Description : P191_fill函数简单示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 17:03
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    int a[5];
    fill(a, a + 5, 0);
    cout << "原始数组是：";
    copy(a, a + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v1(5);
    fill(v1.begin(), v1.end(), 10);
    cout << "vector v1= ";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v2;
    fill_n(back_inserter(v2), 5, 20);
    cout << "vector v2= ";
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}