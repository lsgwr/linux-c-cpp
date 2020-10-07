# 高级语法

## IO流
### IO流基础
![IO流基础](images/IO流基础.jpg)

### IO流类层次结构图
![IO流类层次结构图](images/IO流类层次结构图.jpg)

## 运算符重载举例
```cpp
#include <iostream>

using namespace std;

class Complex {
public:
    Complex();                                    // 默认构造函数
    Complex(double r, double i);      // 构造函数
    virtual ~Complex();                      // 析构函数
    Complex(const Complex &x);      // 拷贝构造
    Complex &operator=(const Complex &c); // =号运算符

    double GetReal() const { return _real; }

    void SetReal(double d) { _real = d; }

    double GetImage() const { return _image; }

    void SetImage(double i) { _image = i; }

    // 运算符重载
    Complex operator+(const Complex &c) const;

    Complex &operator+=(const Complex &c);

    Complex operator-(const Complex &c) const;

    Complex &operator-=(const Complex &c);

    Complex operator*(const Complex &c) const;

    Complex &operator*=(const Complex &c);

    Complex operator/(const Complex &c) const;

    Complex &operator/=(const Complex &c);

    bool operator==(const Complex &c) const;

    bool operator!=(const Complex &c) const;

    bool operator>(const Complex &c) const;

    bool operator>=(const Complex &c) const;

    bool operator<(const Complex &c) const;

    bool operator<=(const Complex &c) const;

    // 前置和后置++
    Complex &operator++();   //前置++
    Complex operator++(int); //后置++
    Complex &operator--();   //前置--
    Complex operator--(int); //后置--

//protected:

    friend ostream &operator<<(ostream &os, const Complex &x);

    friend istream &operator>>(istream &is, Complex &x);

private:
    double _real;             // 复数的实部
    double _image;         // 复数的虚部
};

Complex::Complex() {
    _real = 0.0;
    _image = 0.0;
    //cout << "Complex::Complex()" << endl;
}

Complex::Complex(double r, double i) {
    _real = r;
    _image = i;
    //cout << "Complex::Complex(double r, double i)" << endl;
}

Complex::Complex(const Complex &c) {
    _real = c._real;
    _image = c._image;
    //cout << "Complex::Complex(const Complex& c)" << endl;
}

Complex &Complex::operator=(const Complex &c) {
    if (this != &c) {
        _real = c._real;
        _image = c._image;
    }
    return *this;
}

Complex::~Complex() {
    _real = _image = 0.0;
    //cout << "Complex::~Complex()" << endl;
}

Complex Complex::operator+(const Complex &c) const {
    //Complex tmp;
    //tmp._real = _real + x._real;
    //tmp._image = _image + x._image;
    //return tmp;

    return Complex(_real + c._real, _image + c._image);
}


Complex &Complex::operator+=(const Complex &c) {
    _real += c._real;
    _image += c._image;

    return *this;
}

Complex Complex::operator-(const Complex &c) const {
    return Complex(_real - c._real, _image - c._image);
}

Complex &Complex::operator-=(const Complex &c) {
    _real -= c._real;
    _image -= c._image;

    return *this;
}

Complex Complex::operator*(const Complex &c) const {
    return Complex(_real * c._real - _image * c._image, _real * c._image + _image * c._real);
}

Complex &Complex::operator*=(const Complex &c) {
    Complex tmp(*this);  //拷贝构造函数
    _real = tmp._real * c._real - _image * c._image;
    _image = tmp._real * c._image + tmp._image * c._real;
    return *this;
}

Complex Complex::operator/(const Complex &c) const {
    double t = c._real * c._real + c._image * c._image;
    return Complex((_real * c._real - _image * (-c._image)) / t, (_real * (-c._image) + _image * c._real) / t);
}

Complex &Complex::operator/=(const Complex &c) {
    Complex tmp(*this);  //拷贝构造函数
    double t = c._real * c._real + c._image * c._image;
    _real = (tmp._real * c._real - tmp._image * (-c._image)) / t;
    _image = (tmp._real * (-c._image) + tmp._image * c._real) / t;
    return *this;
}

bool Complex::operator==(const Complex &c) const {
    return (_real == c._real) && (_image == c._image);
}

bool Complex::operator!=(const Complex &c) const {
    return !((_real == c._real) && (_image == c._image));
}

bool Complex::operator>(const Complex &c) const {
    return (_real > c._real) && (_image > c._image);
}

bool Complex::operator>=(const Complex &c) const {
    return (_real >= c._real) && (_image >= c._image);
}

bool Complex::operator<(const Complex &c) const {
    return (_real < c._real) && (_image < c._image);
}

bool Complex::operator<=(const Complex &c) const {
    return (_real <= c._real) && (_image <= c._image);
}


Complex &Complex::operator++() // 前置++
{
    _real++;
    _image++;
    return *this;
}

Complex Complex::operator++(int) // 后置++
{
    //Complex tmp(*this);
    //_real++;
    //_image++;
    //return tmp;
    return Complex(_real++, _image++);
}

Complex &Complex::operator--()   //前置--
{
    _real--;
    _image--;
    return *this;
}

Complex Complex::operator--(int) //后置--
{
    return Complex(_real--, _image--);
}

ostream &operator<<(ostream &os, const Complex &x) {
    os << "real value is  " << x._real << "  image value is " << x._image;
    return os;
}

istream &operator>>(istream &is, Complex &x) {
    is >> x._real >> x._image;
    return is;
}

}
```

## 7-16 深拷贝、浅拷贝、move语义的优化
+ **浅拷贝**：只拷贝指针地址，C++默认拷贝构造函数与赋值运算符重载都是浅拷贝；节省空间，但是容易引起多次释放
+ **深拷贝**：重新分配堆内存，拷贝指针重新指向内容；缺点是浪费空间。但是不会导致多次释放