/***********************************************************
 * @Description : P134_3种形成集合的方法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 22:12
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <set>

using namespace std;

void display(multiset<int> &s) {
    cout << "集合输出：";
    for (int i : s) {
        cout << i << "\t";
    }
    cout << endl;
}

int main() {
    int a[] = {5, 3, 9, 3, 7, 2, 9, 3};
    int nSize = sizeof(a) / sizeof(a[0]);
    multiset<int> mySet;
    for (int i = 0; i < nSize; ++i) {
        mySet.insert(a[i]);
    }
    display(mySet);

    //复制集合
    multiset<int> mySet2(mySet);
    display(mySet2);

    // 通过构造函数创建集合
    multiset<int> mySet3(a, a + nSize);
    display(mySet3);
    return 0;
}
/**
集合输出：2	3	3	3	5	7	9	9
*/