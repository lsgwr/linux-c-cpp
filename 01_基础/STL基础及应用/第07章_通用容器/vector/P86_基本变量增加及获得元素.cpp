/***********************************************************
 * @Description : P86_增加及获得元素
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 10:10
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> intVec;
    intVec.push_back(1);
    intVec.push_back(2);
    intVec.push_back(3);
    int nSize = intVec.size();
    cout << "通过数组方式输出：";
    for (int i = 0; i < nSize; ++i) {
        cout << intVec[i] << "\t";
    }
    cout << endl;

    cout << "通过获得引用输出：" << endl;
    for (int i = 0; i < nSize; ++i) {
        int &nValue = intVec.at(i);
        cout << nValue << "\t";
    }
    cout << endl;

    cout << "通过迭代器输出：" << endl;
    auto intVecIter = intVec.begin();
    while (intVecIter != intVec.end()) {
        cout << *intVecIter << "\t";
        intVecIter++;
    }
    cout << endl;
    return 0;
}