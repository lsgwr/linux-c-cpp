/***********************************************************
 * @Description : P73_绑定和取反适配器基本用法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 21:50
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 3, 5, 7, 9, 8, 6, 4, 2, 0};
    int nCount = count_if(a, a + sizeof(a) / sizeof(int), bind2nd(less<int>(), 4)); // 统计小于4的元素个数
    cout << nCount << endl;
    nCount = count_if(a, a + sizeof(a) / sizeof(int), bind1st(less<int>(), 4)); // 统计大于4的元素个数
    cout << nCount << endl;
    nCount = count_if(a, a + sizeof(a) / sizeof(int), not1(bind2nd(less<int>(), 4))); // 统计不小于4的元素个数
    cout << nCount << endl;
    nCount = count_if(a, a + sizeof(a) / sizeof(int), not1(bind1st(less<int>(), 4))); // 统计不大于4的元素个数
    cout << nCount << endl;
    sort(a, a + sizeof(a) / sizeof(int), not2(less<int>()));
    copy(a, a + sizeof(a) / sizeof(int), ostream_iterator<int>(cout, " "));
    return 0;
}
/**
4
5
6
5
9 8 7 6 5 4 3 2 1 0
*/