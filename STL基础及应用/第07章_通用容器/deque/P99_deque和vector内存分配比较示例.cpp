/***********************************************************
 * @Description : P99_deque和vector内存分配比较示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 16:39
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    vector<int> v(2);
    v[0] = 10;
    int *p = &v[0];
    cout << "vector第1个元素迭代指针：*p=" << *p << endl; //10
    v.push_back(20);
    cout << "vector容量变化后第1个元素迭代指针：*p=" << *p << endl; //不确定

    deque<int> d(2);
    d[0] = 10;
    int *q = &d[0];
    cout << "deque第1个元素迭代指针：*q=" << *p << endl; //10
    d.push_back(20);
    cout << "deque容量变化后第1个元素迭代指针：*q=" << *p << endl; //10，确定地，不会因为添加元素而变
    return 0;
}
/**
vector第1个元素迭代指针：*p=10
vector容量变化后第1个元素迭代指针：*p=0
deque第1个元素迭代指针：*q=0
deque容量变化后第1个元素迭代指针：*q=0
*/