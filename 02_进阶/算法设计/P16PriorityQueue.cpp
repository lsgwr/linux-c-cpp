/***********************************************************
 * @Description : 优先队列
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/12/1 22:31
 * @email       : liangshanguang2@gmail.com
***********************************************************/

#include <iostream>
#include <queue>

using namespace std;

int main() {
    int a[] = {3, 6, 1, 5, 4, 2};
    int n = sizeof(a) / sizeof(a[0]); // 数组长度
    priority_queue<int> pq1(a, a + n); // 优先队列默认使用vector作为容器
    cout << "pq1: ";
    // 优先队列依次弹出元素
    while (!pq1.empty()) {
        cout << pq1.top() << "\t";
        pq1.pop();
    }
    cout << endl;

    priority_queue<int> pq2(a, a + n);
    cout << "pq2: ";
    while (!pq2.empty()) {
        cout << pq2.top() << "\t";
        pq2.pop();
    }
    cout << endl;
}