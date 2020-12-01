/***********************************************************
 * @Description : 迭代器
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/12/1 23:22
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>
#include <list>

using namespace std;

template<typename T>
void printList(list<T> list) {
    for (auto it = list.begin(); it != list.end(); it++) {
        cout << *it << "\t";
    }
    cout << endl;
}

int main() {
    int a[] = {2, 4, 1, 5, 3};
    int n = sizeof(a) / sizeof(a[0]);
    list<int> firstList(a, a + n); // 定义firstList容器
    int b[] = {10, 12, 14, 16};
    int m = sizeof(b) / sizeof(b[0]);
    list<int> secondList(b, b + m);
    auto it = firstList.begin();
    advance(it, 3); // it向后移动3个元素
    insert_iterator<list<int>> insert_it(firstList, it); // 定义firstList地插入迭代器insert_it
    copy(secondList.begin(), secondList.end(), insert_it); // 把secondList元素复制到insert_it处
    cout << "firstList: ";
    printList(firstList);
    cout << "secondList: ";
    printList(secondList);
}