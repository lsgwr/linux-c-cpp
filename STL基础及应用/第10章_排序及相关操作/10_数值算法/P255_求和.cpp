/***********************************************************
 * @Description : P255_求和
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 17:15
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <numeric>
#include <functional>
#include <vector>

using namespace std;

int main() {
    vector<int> v(10);
    for (int i = 0; i < 10; ++i) {
        v[i] = i + 1;
    }
    vector<int> mid(10);
    partial_sum(v.begin(), v.end(), mid.begin(), multiplies<int>());
    int sum = accumulate(mid.begin(), mid.end(), 0);
    cout << "1 + (1 * 2) + (1 * 2 * 3) + ...前10项之和是：" << sum << endl;
    return 0;
}
/**
1 + (1 * 2) + (1 * 2 * 3) + ...前10项之和是：4037913
*/