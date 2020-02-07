/***********************************************************
 * @Description : P62_利用一元函数求向量各元素之和
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 18:56
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

template<class _inPara, class _outPara>
class CSum : public unary_function<_inPara, _outPara> {
public:
    _outPara sum;

    CSum() {
        sum = 0;
    }

    void operator()(_inPara n) {
        sum += n;
    }

    _outPara getSum() {
        return sum;
    }
};

int main() {
    vector<int> v;
    for (int i = 1; i <= 100; ++i) {
        v.push_back(i);
    }
    CSum<int, int> sObj = for_each(v.begin(), v.end(), CSum<int, int>());
    cout << "sum(int)=" << sObj.getSum() << endl;

    vector<float> v2;
    float f = 1.3f;
    for (int i = 1; i <= 99; ++i) {
        v2.push_back(f);
        f += 1.0f;
    }
    CSum<float, float> sObj2 = for_each(v2.begin(), v2.end(), CSum<float, float>());
    cout << "sum(float)=" << sObj2.getSum() << endl;
    return 0;
}