/***********************************************************
 * @Description : P68_非常规数据类型基本函数的使用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 20:25
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <iostream>
#include <vector>
#include <numeric>

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

    Complex operator+(const Complex &c) const {
        Complex v;
        v.real = real + c.real;
        v.virt = virt + c.virt;
        return v;
    }
};

int main() {
    Complex c1(1.0f, 2.0f);
    Complex c2(3.0f, 4.0f);

    // 因为重写了+运算符，实际下面两种加法的写法都是正确的
    Complex c3 = c1 + c2;
    Complex c4 = plus<Complex>()(c1, c2);
    cout << c3.real << "+" << c3.virt << "i" << endl;
    cout << c4.real << "+" << c4.virt << "i" << endl;

    Complex c;
    vector<Complex> v;
    v.push_back(c1);
    v.push_back(c2);
    v.push_back(c3);
    v.push_back(c4);
    Complex result = accumulate(v.begin(), v.end(), c, plus<Complex>());
    cout << result.real << "+" << result.virt << "i" << endl;
    return 0;
}