/***********************************************************
 * @Description : P91_删除元素
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 11:40
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> intVec;
    for (int i = 1; i <= 10; ++i) {
        intVec.push_back(i);
    }

    // 删除第5个元素
    intVec.erase(intVec.begin() + 4);
    cout << "删除第5个元素后的vector：";
    for (int i : intVec) {
        cout << i << "\t";
    }
    cout << endl;

    // 再删除第2~5个元素
    intVec.erase(intVec.begin() + 1, intVec.begin() + 5);
    cout << "删除第2~5个元素后的vector：";
    for (int i : intVec) {
        cout << i << "\t";
    }
    return 0;
}