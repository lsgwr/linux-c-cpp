/***********************************************************
 * @Description : 类模板的定义和实例化
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/13 22:40
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>

using namespace std;

template<class T>
class Operates {
public:
    T a;

    Operates() {}

    Operates(T a) : a(a) {}

    T add(T b) {
        return this->a + b;
    }

    T sub(T b) {
        return this->a - b;
    }

    T mul(T b) {
        return this->a * b;
    }

    T div(T b) {
        return this->a / b;
    }
};

int main() {
    Operates<int> a(10);
    int b = 10;
    cout << a.add(b) << endl;
    cout << a.sub(b) << endl;
    cout << a.mul(b) << endl;
    cout << a.div(b) << endl;
    return 0;
}