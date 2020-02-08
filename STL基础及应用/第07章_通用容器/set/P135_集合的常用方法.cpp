/***********************************************************
 * @Description : P135_集合的常用方法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 22:24
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <set>

using namespace std;

int main() {
    int a[] = {5, 3, 9, 3, 7, 2, 9, 3};
    int nSize = sizeof(a) / sizeof(a[0]);
    set<int> mySet(a, a + nSize);
    cout << "集合原始数据是：";
    for (int num : mySet) {
        cout << num << "\t";
    }
    cout << endl;

    multiset<int> myMultiset(a, a + nSize);
    cout << "多集合原始数据是：";
    for (int num : myMultiset) {
        cout << num << "\t";
    }
    cout << endl;

    pair<set<int>::iterator, set<int>::iterator> rangeSet;
    pair<multiset<int>::iterator, multiset<int>::iterator> rangeMultiSet;

    // 返回集合中等于3的迭代器指针，用pair函数接收
    rangeSet = mySet.equal_range(3);
    cout << "集合中等于2的元素：";
    auto setIt = rangeSet.first;
    while (setIt != rangeSet.second) {
        cout << *setIt << "\t";
        setIt++;
    }
    cout << endl;

    // 返回多集合中等于3的迭代器指针，用pair接收
    rangeMultiSet = myMultiset.equal_range(3);
    cout << "多集合中等于3的元素：";
    auto multiSetIt = rangeMultiSet.first;
    while (multiSetIt != rangeMultiSet.second) {
        cout << *multiSetIt << "\t";
        multiSetIt++;
    }
    cout << endl;
    // 求集合中等于3的元素个数
    int nCount = mySet.count(3);
    // 求多集合中等于3的元素个数
    int nMultiCount = myMultiset.count(3);
    return 0;
}
/**
集合原始数据是：2	3	5	7	9
多集合原始数据是：2	3	3	3	5	7	9	9
集合中等于2的元素：3
多集合中等于3的元素：3	3	3
*/