/***********************************************************
 * @Description : P179_copy示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 15:32
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[5];
    vector<int> v;

    copy(a, a + 5, b); // a数组复制到b数组
    copy(a, a + 5, back_inserter(v)); // a数组复制到向量vector中

    cout << "原始a数组为：";
    copy(a, a + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "b数组为：";
    copy(b, b + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "vector为：";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    return 0;
}