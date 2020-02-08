/***********************************************************
 * @Description : P117_queue的基本操作
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 18:15
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <queue>

using namespace std;

/**
 * 队列遍历模板函数
 * @tparam T 元素类型
 * @tparam Container 实现堆栈的容器类型
 * @param obj 堆栈对象
 */
template<class T, class Container>
void printQueue(queue<T, Container> obj) {
    cout << "遍历结果是：";
    while (!obj.empty()) {
        cout << obj.front() << "\t";
        obj.pop();
    }
    cout << endl;
}

int main() {
    string str = "a"; // 字符串队列
    queue<string, deque<string>> strQueue;
    for (int i = 0; i < 4; ++i) {
        strQueue.push(str);
        str += "a";
    }
    printQueue(strQueue);

    queue<float, list<float>> fltQueue; // 浮点队列
    for (int i = 0; i < 4; ++i) {
        fltQueue.push(i+1);
    }
    printQueue(fltQueue);
    return 0;
}
/**
遍历结果是：a	aa	aaa	aaaa
遍历结果是：1	2	3	4
*/