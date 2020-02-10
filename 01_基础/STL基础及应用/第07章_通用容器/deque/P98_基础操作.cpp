/***********************************************************
 * @Description : P98_基础操作
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 16:23
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> queue;
    queue.push_back(10);
    queue.push_back(20);
    queue.push_back(30);
    cout << "原始双端队列：";
    for (int i : queue) {
        cout << i << "\t";
    }
    cout << endl;

    queue.push_front(5);
    queue.push_front(3);
    queue.push_front(1);
    cout << "push_front(5,3,1)后：";
    for (int i:queue) {
        cout << i << "\t";
    }
    cout << endl;

    queue.pop_front();
    queue.pop_front();
    cout << "两次pop_front后：";
    for (int i:queue) {
        cout << i << "\t";
    }
    cout << endl;
    return 0;
}