/***********************************************************
 * @Description : P122_整型序列进出优先队列
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 19:11
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    int a[] = {1232, 67, 34, 8, 2, 4, 9, 67, 78, 123};
    // 默认是降序，所以下面的代码可以简化成priority_queue<int> pq(a, a + 9);
    priority_queue<int, vector<int>, less<int>> pq(a, a + 9);
    pq.push(a[9]);

    while (!pq.empty()) {
        cout << pq.top() << "\t";
        pq.pop();
    }
    return 0;
}
/**
1232	123	78	67	67	34	9	8	4	2
*/