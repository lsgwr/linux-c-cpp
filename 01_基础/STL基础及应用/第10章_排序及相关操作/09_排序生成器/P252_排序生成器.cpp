/***********************************************************
 * @Description : P252_排序生成器
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 17:03
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int A[] = {2, 3, 4, 5, 6, 1};
    const int N = sizeof(A) / sizeof(A[0]);

    cout << "初始化：";
    copy(A, A+N, ostream_iterator<int>(cout, " "));
    cout << endl;

    prev_permutation(A, A+N);
    cout << "上一个排列是：";
    copy(A, A+N, ostream_iterator<int>(cout, " "));
    cout << endl;

    next_permutation(A, A+N);
    cout << "下一个排列是：";
    copy(A, A+N, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
/**
初始化：2 3 4 5 6 1
上一个排列是：2 3 4 5 1 6
下一个排列是：2 3 4 5 6 1
*/