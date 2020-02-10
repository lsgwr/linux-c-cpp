/***********************************************************
 * @Description : P255_内积之和
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 17:19
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    vector<float> v(10);
    for (int i = 0; i < 10; ++i) {
        v.push_back((float) (i + 1) / (i + 2));
        cout << (float) (i + 1) / (i + 2) << "\t";
    }
    cout << endl;
    float sum = inner_product(v.begin(), v.end(), v.begin(), 0.0f); // 向量自身做内积

    cout << "内积是：" << sum << endl;
    return 0;
}
/**
0.5	0.666667	0.75	0.8	0.833333	0.857143	0.875	0.888889	0.9	0.909091
内积是：6.51828
*/