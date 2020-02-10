/***********************************************************
 * @Description : P71_利用二元函数比较两个复数是否相等
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 21:23
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <iostream>

using namespace std;

class Complex {
public:
    float real; // 实部
    float virt; // 虚部

    Complex() {
        this->real = 0.0f;
        this->virt = 0.0f;
    }

    Complex(float real, float virt) : real(real), virt(virt) {}

    bool operator==(const Complex &c) const {
        return ((real == c.real) && (virt == c.virt));
    }
};

int main() {
    Complex c1(1.0f, 2.0f);
    Complex c2(3.0f, 4.0f);
    Complex c3(1.0f, 2.0f);
    cout << equal_to<Complex>()(c1, c2) << endl;
    cout << equal_to<Complex>()(c1, c3) << endl;
    return 0;
}
/**
0
1
 */
