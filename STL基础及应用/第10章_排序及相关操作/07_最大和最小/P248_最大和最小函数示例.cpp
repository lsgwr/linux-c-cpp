/***********************************************************
 * @Description : P248_最大和最小函数示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 12:21
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a = min(10, 20);
    int b = max(10, 20);
    cout << "较小值：" << a << endl;
    cout << "较大值：" << b << endl;

    int c[] = {1, 10, 5, 7, 9};
    int *it_min = min_element(c, c + 5);
    int *it_max = max_element(c, c + 5);
    cout << "c[]最小值：" << *it_min << endl;
    cout << "c[]最大值：" << *it_max << endl;
    return 0;
}
/**
较小值：10
较大值：20
c[]最小值：1
c[]最大值：10
*/