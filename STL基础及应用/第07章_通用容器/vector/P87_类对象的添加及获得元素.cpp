/***********************************************************
 * @Description : P87_类对象的添加及获得元素
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 10:33
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <vector>
#include <iostream>

using namespace std;

class A {
public:
    int n;

    A(int n) : n(n) {}
};

int main() {
    cout << "第一部分：类A的向量操作" << endl;
    vector<A> caVec; // 类A的向量定义
    A a1(1);
    A a2(2);
    caVec.push_back(a1);
    caVec.push_back(a2);
    int nSize = caVec.size();

    cout << "通过数组输出：";
    for (int i = 0; i < nSize; ++i) {
        cout << caVec[i].n << "\t";
    }
    cout << endl;

    cout << "通过引用输出：";
    for (int i = 0; i < nSize; ++i) {
        A &a = caVec.at(i);
        cout << a.n << "\t";
    }
    cout << endl;

    cout << "通过迭代器输出：";
    auto caVecIter = caVec.begin();
    while (caVecIter != caVec.end()) {
        cout << (*caVecIter).n << "\t";
        caVecIter++;
    }
    cout << endl;

    cout << "第二部分：类A的指针向量操作" << endl;
    vector<A *> pcaVec; // 类A的指针向量定义
    A *pa1 = new A(1);
    A *pa2 = new A(2);
    pcaVec.push_back(pa1);
    pcaVec.push_back(pa2);
    nSize = pcaVec.size();

    cout << "通过数组输出：";
    for (int i = 0; i < nSize; ++i) {
        cout << pcaVec[i]->n << "\t";
    }
    cout << endl;

    cout << "通过引用输出：";
    for (int i = 0; i < nSize; ++i) {
        A *&a = pcaVec.at(i);
        cout << a->n << "\t";
    }
    cout << endl;

    cout << "通过迭代器输出：";
    auto pcaVecIter = pcaVec.begin();
    while (pcaVecIter != pcaVec.end()) {
        cout << (**pcaVecIter).n << "\t";
        pcaVecIter++;
    }
    delete pa1;
    delete pa2;
    return 0;
}