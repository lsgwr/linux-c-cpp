#include <iostream>
#include <assert.h>

using namespace std;

// 编写一个函数，输入两个int型变量a,b
// 实现在函数内部将a,b的值进行交换。
void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap2(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int x = 1, x2 = 3;
    int &rx = x;
    rx = 2;
    cout << x << endl;     // 2
    cout << rx << endl;    // 2
    rx = x2;
    cout << x << endl;     // 3
    cout << rx << endl;    // 3

    // 交换变量的测试
    int a = 3, b = 4;
    swap(a, b);   // 引用交换
    assert(a == 4 && b == 3);

    a = 3, b = 4;
    swap2(&a, &b);
    assert(a == 4 && b == 3);


    return 0;
}