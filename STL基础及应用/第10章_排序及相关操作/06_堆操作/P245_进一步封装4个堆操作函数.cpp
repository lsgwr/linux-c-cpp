/***********************************************************
 * @Description : P245_进一步封装4个堆操作函数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 11:34
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;

template<class T, class Pred=less<T>>
class MyHeap {
    Pred pr;
    vector<T> v;
    int validSize;

public:
    MyHeap(T t[], int nSize) : v(t, t + nSize) {
        // 建立堆
        validSize = nSize;
        make_heap(v.begin(), v.begin() + validSize, pr);
    }

    /**
     * 向堆中添加新元素
     */
    void insert(const T &t) {
        v.push_back(t);
        validSize++;
        push_heap(v.begin(), v.begin() + validSize, pr);
    }

    /**
     * 获得堆中的最大值和最小值
     * @param result
     * @return
     */
    bool remove(T &result) {
        if (validSize == 0) {
            return false;
        }
        pop_heap(v.begin(), v.begin() + validSize, pr);
        result = *(v.begin() + validSize - 1);
        validSize--;
        return true;
    }

    void sort() {
        if (validSize > 0) {
            sort_heap(v.begin(), v.begin() + validSize);
        }
    }

    bool isEmpty() {
        return validSize == 0;
    }

    void display() {
        copy(v.begin(), v.begin() + validSize, ostream_iterator<T>(cout, "\t"));
    }
};

int main() {
    int a[] = {1, 4, 2, 10, 6};
    MyHeap<int, greater<int>> m(a, 5); // 产生一个最小堆
    cout << "原始堆：";
    m.display();
    cout << endl;

    m.insert(100);
    cout << "插入100后堆变成：";
    m.display();
    cout << endl;

    int result;
    m.remove(result);
    cout << "堆中最小值：" << result << endl;
    m.remove(result);
    cout << "堆中次小值：" << result << endl;
    return 0;
}
/**
原始堆：1	4	2	10	6
插入100后堆变成：1	4	2	10	6	100
堆中最小值：1
堆中次小值：2
*/