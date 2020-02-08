/***********************************************************
 * @Description : P100_用deque实现一个先进先出的队列
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 16:50
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <deque>

using namespace std;

template<class T>
class MyQueue {
    deque<T> d;

public:
    /**
     * 向队尾添加元素
     * @param t 要添加的元素
     */
    void push(const T &t) {
        d.push_back(t);
    }

    /**
     * 删除队头元素
     */
    void pop() {
        d.pop_front();
    }

    /**
     * 获取队列大小
     * @return 队列的大小
     */
    int size() {
        return d.size();
    }

    /**
     * 队列是否为空
     */
    bool empty() {
        return d.empty();
    }

    /**
     * 获取队头元素
     */
    T &front() {
        return *d.begin();
    }

    /**
     * 获取队尾元素
     */
    T &back() {
        return *(--d.end());
    }

    void display() {
        for (T t : d) {
            cout << t << "\t";
        }
        cout << endl;
    }
};

int main() {
    MyQueue<int> queue;
    for (int i = 0; i < 5; ++i) {
        queue.push(i + 1);
    }

    cout << "原队列：";
    queue.display();
    cout << "删除队头元素后：";
    queue.pop();
    queue.display();
    cout << "插入队尾元素6后：";
    queue.push(6);
    queue.display();
    cout << "当前队头元素：";
    cout << queue.front() << endl;
    cout << "当前队尾元素：";
    cout << queue.back() << endl;
    return 0;
}
/**
原队列：1	2	3	4	5
删除队头元素后：2	3	4	5
插入队尾元素6后：2	3	4	5	6
当前队头元素：2
当前队尾元素：6
*/