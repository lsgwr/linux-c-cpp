/***********************************************************
 * @Description : P224_利用partial_sort取整型向量最小的4个元素
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 22:14
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main() {
    int a[] = {10, 1, 3, 9, 7, 6, 2, 4, 5, 8};
    vector<int> v(a, a + 10);
    cout << "原始向量数据为：";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "前4个元素升序排列：";
    partial_sort(v.begin(), v.begin() + 4, v.end());
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
原始向量数据为：10	1	3	9	7	6	2	4	5	8
前4个元素升序排列：1	2	3	4	10	9	7	6	5	8
*/