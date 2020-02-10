/***********************************************************
 * @Description : P222_使用sort对整型向量升序排列
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 21:40
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;


bool myLess(int &m, int &n) {
    return m > n;
}

int main() {
    int a[] = {1, 8, 6, 10, 4};
    vector<int> v(a, a + 5);
    sort(v.begin(), v.end(), myLess);
    cout << "升序排序结果是：";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    return 0;
}
/**
 * 升序排序结果是：10	8	6	4	1
 */
