/***********************************************************
 * @Description : P105_sort_merge_splice
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 17:38
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> l1;
    l1.push_back(1);
    l1.push_back(5);
    l1.push_back(3);
    l1.push_back(10);

    list<int> l2;
    l2.push_back(2);
    l2.push_back(8);
    l2.push_back(6);
    l2.push_back(9);

    l1.sort();
    l2.sort();

    l1.merge(l2);
    cout << "拼接之后的list：";
    for (int i: l1) {
        cout << i << "\t";
    }
    cout << endl;
    cout << "拼接之后两个列表的长度：" << l1.size() << "\t" << l2.size() << endl;
    return 0;
}
/**
拼接之后的list：1	2	3	5	6	8	9	10
拼接之后两个列表的长度：8	0
*/