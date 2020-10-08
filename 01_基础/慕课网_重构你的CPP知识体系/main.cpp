#include <iostream>

using namespace std;

// 一元函数的参数和返回值类型，通常被继承
template<class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

// 二元函数的参数和返回值类型，通常被继承
template<class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

int main() {
    return 0;
}