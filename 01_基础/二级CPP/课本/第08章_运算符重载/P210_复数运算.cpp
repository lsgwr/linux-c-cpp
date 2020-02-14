/***********************************************************
 * @Description : 复数运算
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/13 22:08
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>

using namespace std;

class Complex {
private:
    double real; // 实部
    double imag; // 虚部
public:
    Complex() {
        real = 0;
        imag = 0;
    }

    Complex(double real, double imag) : real(real), imag(imag) {}

    /**
     * 重载+运算符
     * @param c1
     * @return
     */
    Complex operator+(Complex &c1) {
        Complex c;
        c.real = this->real + c1.real;
        c.imag = this->imag + c1.imag;
        return c;
    }

    void display() {
        cout << "(" << real << ", " << imag << "i)" << endl;
    }
};

int main() {
    Complex c1(13, 24), c2(35, -32), c3;
    c3 = c1 + c2;
    cout << "c1 = ";
    c1.display();
    cout << "c2 = ";
    c2.display();
    cout << "c1 + c2 = ";
    c3.display();
    return 0;
}