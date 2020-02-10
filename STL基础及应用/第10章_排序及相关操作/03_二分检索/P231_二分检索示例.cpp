/***********************************************************
 * @Description : P231_二分检索示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 23:35
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

int main() {
    // Todo:
    int a[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    list<int> l1(a, a + 10);
    cout << "原始数据a[]：";
    copy(l1.begin(), l1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    bool bExist = binary_search(l1.begin(), l1.end(), 5);
    cout << "有元素5吗？" << (bExist == 0 ? "false" : "true") << endl;
    auto first2 = lower_bound(l1.begin(), l1.end(), 2);
    if (first2 != l1.end()) {
        cout << "第一个元素2的位置：" << distance(l1.begin(), first2) << endl;
    }

    auto last3 = upper_bound(l1.begin(), l1.end(), 3);
    if (last3 != l1.end()) {
        cout << "最后一个元素3的位置：" << distance(l1.begin(), --last3) << endl;
    }
    auto p = equal_range(l1.begin(), l1.end(), 4);
    if (p.first != p.second) {
        int nSize = distance(p.first, p.second);
        cout << "共有元素4的个数：" << nSize << endl;
    }
    return 0;
}
/**
原始数据a[]：1	2	2	3	3	3	4	4	4	4
有元素5吗？false
第一个元素2的位置：1
最后一个元素3的位置：5
共有元素4的个数：4
*/