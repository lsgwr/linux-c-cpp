/***********************************************************
 * @Description : P61_求整型向量各元素之和
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 18:34
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/


class CSum {
private:
    int sum;

public:
    CSum() {
        sum = 0;
    }

    void operator()(int n) {
        sum += n;
    }

    int getSum() {
        return sum;
    }
};

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v;
    for (int i = 0; i <= 100; ++i) {
        v.push_back(i);
    }
    // 对每个v中的元素执行CSum中的operator
    CSum sObj = for_each(v.begin(), v.end(), CSum());
    cout << "sum=" << sObj.getSum() << endl;
    return 0;
}
/**
 * sum=5050
 */
