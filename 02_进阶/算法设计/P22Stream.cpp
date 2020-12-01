/***********************************************************
 * @Description : 流迭代器
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/12/1 23:35
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {2, 4, 1, 5, 3};
    int n = sizeof(a) / sizeof(a[0]);
    vector<int> myV(a, a + n);
    sort(myV.begin(), myV.end()); // 默认递增排序
    ostream_iterator<int> outs(cout, "\t"); // 定义ostream迭代器，第二个参数表示分隔符
    cout << "myV: ";
    copy(myV.begin(), myV.end(), outs);
    cout << endl;
}