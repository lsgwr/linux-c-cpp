/***********************************************************
 * @Description : P118_实现一个大小固定的堆栈类
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 18:25
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <deque>
#include <stack>

using namespace std;

template<class T, class Container=deque<T>>
class MyStack : public stack<T, Container> {
private:
    int maxSize; // 堆栈的最大大小

public:
    MyStack(int maxSize) : maxSize(maxSize) {}

    /**
     * 重载push函数
     */
    void push(const T &t) {
        if (stack<T, Container>::size() < maxSize) {
            // 堆栈还没满才能往里面添加
            stack<T, Container>::push(t);
        } else {
            cout << "堆栈满了，" << t << "无法插入！" << endl;
        }
    }
};

int main() {
    MyStack<int, deque<int>> intStack(2);  // 设置最大为2的堆栈
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    return 0;
}
/**
堆栈满了，3无法插入！
*/