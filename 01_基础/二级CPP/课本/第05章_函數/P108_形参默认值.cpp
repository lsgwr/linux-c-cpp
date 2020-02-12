/***********************************************************
 * @Description : 形参默认值
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/12 18:45
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

int max(int a, int b, int c = 0) {
    if (b > a) {
        a = b;
    }
    if (c > a) {
        a = c;
    }
    return a;
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << max(a, b) << endl;
    cout << max(a, b, c) << endl;
    return 0;
}
/**
12 13 14
12 13 14
13
14
*/