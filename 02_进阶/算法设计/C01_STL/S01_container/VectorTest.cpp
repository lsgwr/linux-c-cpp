/***********************************************************
 * @Description : 
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/11/30 23:37
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void printVector(vector<T> v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v1;
    vector<int> v2(10); // 初始化有10个元素的vector
    vector<double> v3(10, 1.23); // 初始化10个元素的vector，每个元素的值都是1.23
    vector<int> v4(a, a + 5); // 用数组a的前5个元素来初始化v4
    printVector(v1);
    printVector(v2);
    printVector(v3);
    printVector(v4);
}