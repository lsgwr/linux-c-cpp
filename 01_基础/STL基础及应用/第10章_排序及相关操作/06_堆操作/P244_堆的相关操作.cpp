/***********************************************************
 * @Description : P244_堆的相关操作
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 11:25
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 4, 2, 10, 6, 5, 9, 7, 8, 3};

    cout << "原始a[]：";
    copy(a, a + 10, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v1(a, a + 10);
    make_heap(v1.begin(), v1.end(), greater<int>());
    cout << "最小堆：";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v2(a, a + 10);
    make_heap(v2.begin(), v2.end(), less<int>());
    cout << "最大堆：";
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    pop_heap(v2.begin(), v2.end());
    cout << "堆中最大值：";
    cout << *(v2.end() - 1) << endl;
    pop_heap(v2.begin(), v2.end() - 1);
    cout << "堆中次大值：";
    cout << *(v2.end() - 2) << endl;
    return 0;
}
/**
原始a[]：1	4	2	10	6	5	9	7	8	3
最小堆：1	3	2	7	4	5	9	10	8	6
最大堆：10	8	9	7	6	5	2	1	4	3
堆中最大值：10
堆中次大值：9
*/