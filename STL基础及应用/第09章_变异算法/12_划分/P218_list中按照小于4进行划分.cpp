/***********************************************************
 * @Description : P218_list中按照小于4进行划分
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 21:16
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 7, 3, 6, 4, 10, 9, 5, 2, 8};
    list<int> v(a, a + 10);
    auto mid = partition(v.begin(), v.end(), bind2nd(less<int>(), 4));
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    int nSize = distance(v.begin(), mid);
    cout << nSize << endl;
    return 0;
}
/**
1	2	3	6	4	10	9	5	7	8
3
*/