/***********************************************************
 * @Description : P104_基本操作
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 17:10
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() {
    list<string> l;
    l.push_back("back");
    l.push_front("middle");
    l.push_front("front");

    cout << "遍历结果：";
    for (const string &str:l) {
        cout << str << "\t";
    }
    cout << endl;

    cout << "第一个元素：" << l.front() << endl; // front
    cout << "第一个元素：" << *l.begin() << endl; // front

    cout << "最后一个元素：" << l.back() << endl;
    cout << "最后一个元素：" << *(l.rbegin()) << endl;

    l.pop_front();
    cout << "遍历结果：";
    for (const string &str:l) {
        cout << str << "\t";
    }
    cout << endl;

    l.pop_back();
    cout << "遍历结果：";
    for (const string &str:l) {
        cout << str << "\t";
    }
    cout << endl;
    return 0;
}
/**
遍历结果：front	middle	back
第一个元素：front
第一个元素：front
最后一个元素：back
最后一个元素：back
遍历结果：middle	back
遍历结果：middle
*/