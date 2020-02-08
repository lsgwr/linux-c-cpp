/***********************************************************
 * @Description : P105_list遍历示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 17:22
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() {
    list<int> l;
    for (int i = 0; i < 5; ++i) {
        l.push_back(i + 1);
    }
    // 显示
    auto it = l.begin();
    while (it != l.end()) {
        cout << *it << "\t";
        it++;
    }
    cout << endl;

    // 反向显示
    auto rit = l.rbegin();
    while (rit != l.rend()) {
        cout << *rit << "\t";
        rit++;
    }
    cout << endl;
    return 0;
}
/**
1	2	3	4	5
5	4	3	2	1
*/