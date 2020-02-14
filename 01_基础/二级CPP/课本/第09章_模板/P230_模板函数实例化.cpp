/***********************************************************
 * @Description : P230_模板函数实例化
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/13 22:28
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>

using namespace std;

template<class T, class B>
T mul(T a, B b) {
    return a * b;
}

int main() {
    int a = 10, b = 1;
    cout << mul(a, b) << endl;
    double ad = 10.2;
    double bd = 1.1;
    cout << mul(ad, bd) << endl;
    float af = 10.1;
    float bf = 1.2;
    cout << mul(af, bf) << endl;
    return 0;
}