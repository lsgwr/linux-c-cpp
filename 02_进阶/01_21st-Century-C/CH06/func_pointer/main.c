#include <stdio.h>

double a_fn(int first, int second) {
    return first + second;
}

double b_fn(int first, int second) {
    return first * second;
}

double c_fn(int first, int second) {
    return first - second;
}

double d_fn(int first, int second) {
    return first / second;
}

typedef double (*x_fn)(int, int); // 定义函数指针类型，可以指向上面的a_fn同形式的所有函数

double apply_fn(x_fn f, int first, int second) {
    return f(first, second);
}

int main() {
    printf("a_fn(4, 2) = %f\n", apply_fn(a_fn, 4, 2));
    printf("b_fn(4, 2) = %f\n", apply_fn(b_fn, 4, 2));
    printf("c_fn(4, 2) = %f\n", apply_fn(c_fn, 4, 2));
    printf("d_fn(4, 2) = %f\n", apply_fn(d_fn, 4, 2));
    return 0;
}
/**
a_fn(4, 2) = 6.000000
b_fn(4, 2) = 8.000000
c_fn(4, 2) = 2.000000
d_fn(4, 2) = 2.000000
*/