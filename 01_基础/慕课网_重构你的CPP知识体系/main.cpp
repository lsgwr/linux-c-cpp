#include <iostream>

using namespace std;

///////////////////   算术类仿函数 + - * / %    ///////////////////
// 1.加法仿真函数，生成一个对象，里面仅有一个函数重载的方法
template<class T>
struct plu : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const {
        return x + y;
    }
};

// 2.减法仿真函数，生成一个对象，里面仅有一个函数重载的方法
template<class T>
struct miu : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const {
        return x - y;
    }
};

// 3.乘法仿真函数，生成一个对象，里面仅有一个函数重载的方法
template<class T>
struct mul : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const {
        return x * y;
    }
};

// 4.除法仿真函数，生成一个对象，里面仅有一个函数重载的方法
template<class T>
struct did : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const {
        return x / y;
    }
};

// 5.除法仿真函数，生成一个对象，里面仅有一个函数重载的方法
template<class T>
struct mod : public binary_function<T, T, T> {
    T operator()(const T &x, const T &y) const {
        return x % y;
    }
};

// 6.取反仿真函数，生成一个对象，里面仅有一个函数重载的方法
template<class T>
struct neg : public unary_function<T, T> {
    T operator()(const T &x) const {
        return -x;
    }
};

// 单独使用仿函数，通常将仿函数和算法单独分开使用
int main() {
    cout << plu<int>()(10, 5) << endl; // 15
    cout << miu<int>()(10, 5) << endl; // 5
    cout << mul<int>()(10, 5) << endl; // 50
    cout << did<int>()(10, 5) << endl; // 2
    cout << mod<int>()(10, 5) << endl; // 0
    cout << neg<int>()(10) << endl; // -10
    return 0;
}