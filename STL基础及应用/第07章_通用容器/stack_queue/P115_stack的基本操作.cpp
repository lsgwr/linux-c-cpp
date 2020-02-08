/***********************************************************
 * @Description : stack的基本操作
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 17:53
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>

using namespace std;

/**
 * 栈遍历函数
 * @param obj
 */
void printStack(stack<int, vector<int>> obj) {
    cout << "遍历结果是：";
    while (!obj.empty()) {
        cout << obj.top() << "\t";
        obj.pop();
    }
    cout << endl;
}

/**
 * 栈遍历函数
 * @param obj
 */
void printStack(stack<string, vector<string>> obj) {
    cout << "遍历结果是：";
    while (!obj.empty()) {
        cout << obj.top() << "\t";
        obj.pop();
    }
    cout << endl;
}


/**
 * 堆栈遍历模板函数
 * @tparam T 元素类型
 * @tparam Container 实现堆栈的容器类型
 * @param obj 堆栈对象
 */
template<class T, class Container>
void printStack(stack<T, Container> obj) {
    cout << "遍历结果是：";
    while (!obj.empty()) {
        cout << obj.top() << "\t";
        obj.pop();
    }
    cout << endl;
}

int main() {
    stack<int, vector<int>> intStack; // 整型堆栈
    for (int i = 0; i < 4; ++i) {
        intStack.push(i + 1);
    }
    printStack(intStack);

    string s = "a";
    stack<string, list<string>> strStack; // 字符串堆栈
    for (int i = 0; i < 4; ++i) {
        strStack.push(s);
        s+="a";
    }
    printStack(strStack);

    stack<float, deque<float>> fltStack; // 浮点堆栈
    for (int i = 0; i < 4; ++i) {
        fltStack.push(i+1);
    }
    printStack(fltStack);
    return 0;
}
/**
遍历结果是：4	3	2	1
遍历结果是：aaaa	aaa	aa	a
遍历结果是：4	3	2	1
*/