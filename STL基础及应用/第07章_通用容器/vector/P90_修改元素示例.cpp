/***********************************************************
 * @Description : P90_修改元素示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 11:17
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> intVec;
    intVec.push_back(1);
    intVec.push_back(2);
    intVec.push_back(3);
    int nSize = intVec.size();
    cout << "通过数组方式输出：";
    intVec[1] = 5;
    for (int i = 0; i < nSize; ++i) {
        cout << intVec[i] << "\t";
    }
    cout << endl;

    cout << "通过获得引用输出：";
    int &m = intVec.at(1);
    m = 10;
    for (int i = 0; i < nSize; ++i) {
        int &nValue = intVec.at(i);
        cout << nValue << "\t";
    }
    cout << endl;

    cout << "通过迭代器输出：";
    auto intVecIter = intVec.begin();
    intVecIter++;
    *intVecIter = 20;
    while (intVecIter != intVec.end()) {
        cout << *intVecIter << "\t";
        intVecIter++;
    }
    cout << endl;
    return 0;
}
/**
通过数组方式输出：1	5	3
通过获得引用输出：1	10	3
通过迭代器输出：20	3
*/