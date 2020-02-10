/***********************************************************
 * @Description : P76_普通函数适配器使用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 22:51
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

bool f(int x) {
    return x > 3;
}

bool g(int x, int y) {
    return x > y;
}

int main() {
    int a[] = {2, 5, 3, 7, 1, 9, 8, 0, 6};
    int nSize = sizeof(a) / sizeof(int);
    int nCount = count_if(a, a + nSize, f); // 大于3的元素的个数
    cout << nCount << endl;
    nCount = count_if(a, a + nSize, ptr_fun(f));
    cout << nCount << endl;
    nCount = count_if(a, a + nSize, bind2nd(ptr_fun(g), 3)); // bind2nd(ptr_fun(g), 3)等效于g(x, 3)
    cout << nCount << endl;
    nCount = count_if(a, a + nSize, bind2nd(ptr_fun(g), 5)); // bind2nd(ptr_fun(g), 5)等效于g(x, 5)
    cout << nCount << endl;
    return 0;
}
/**
5
5
5
4
*/