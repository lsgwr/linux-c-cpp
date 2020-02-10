/***********************************************************
 * @Description : P237_集合操作简单示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 10:51
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 6};
    list<int> l1(a, a + 5);
    list<int> l2(b, b + 4);

    // 包含
    bool bRet = includes(l1.begin(), l1.end(), l2.begin(), l2.end());
    cout << "l1包含l2?" << (bRet == 1 ? "yes" : "no") << endl;

    // l1并l2
    list<int> l3;
    set_union(l1.begin(), l1.end(), l2.begin(), l2.end(), back_inserter(l3));
    cout << "l1并l2的结果是：";
    copy(l3.begin(), l3.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    // l1交l2
    list<int> l4;
    set_intersection(l1.begin(), l1.end(), l2.begin(), l2.end(), back_inserter(l4));
    cout << "l1交l2：";
    copy(l4.begin(), l4.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    // l1差l2
    list<int> l5;
    set_difference(l1.begin(), l1.end(), l2.begin(), l2.end(), back_inserter(l5));
    cout << "l1差l2：";
    copy(l5.begin(), l5.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    list<int> l6;
    set_symmetric_difference(l1.begin(), l1.end(), l2.begin(), l2.end(), back_inserter(l6));
    cout << "l1对称差l2：";
    copy(l6.begin(), l6.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
l1包含l2?no
l1并l2的结果是：1	2	3	4	5	6
l1交l2：1	2	3
l1差l2：4	5
l1对称差l2：4	5	6
*/