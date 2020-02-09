/***********************************************************
 * @Description : P161_7个查询函数的简单应用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 10:26
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <algorithm>
#include <iostream>

using namespace std;

bool myGreater(int m) {
    return m > 4;
}

int main() {
    int arr[] = {1, 2, 2, 2, 3, 4, 4, 5, 6, 7, 1, 2, 2, 3};
    int nSize = sizeof(arr) / sizeof(arr[0]);

    cout << "原始数组：";
    for (int i = 0; i < nSize; ++i) {
        cout << arr[i] << "\t";
    }
    cout << endl;

    int *p1 = find(arr, arr + nSize, 3);
    if (p1 != arr + nSize) {
        cout << "首次等于3的位置：" << p1 - arr << endl;
    }

    int *p2 = find_if(arr, arr + nSize, myGreater);
    if (p2 != arr + nSize) {
        cout << "首次大于4的位置：" << p2 - arr << endl;
    }

    int b[] = {10, 12, 6};
    int nSize2 = sizeof(b) / sizeof(b[0]);
    int *p3 = find_first_of(arr, arr + nSize, b, b + nSize2);
    if (p3 != arr + nSize) {
        cout << "首次在arr中发现b数组元素的位置：" << p3 - arr << endl;
    }

    int *p4 = adjacent_find(arr, arr + nSize);
    if (p4 != arr + nSize) {
        cout << "首次相邻元素相同的位置：" << p4 - arr << endl;
    }

    int c[] = {2, 3};
    int nSize3 = sizeof(c) / sizeof(c[0]);
    int *p5 = find_end(arr, arr + nSize, c, c + nSize3);
    if (p5 != arr + nSize) {
        cout << "最后一次匹配数组c的位置：" << p5 - arr << endl;
    }

    int *p6 = search(arr, arr + nSize, c, c + nSize3);
    if (p6 != arr + nSize) {
        cout << "首次匹配数组c的位置：" << p6 - arr << endl;
    }

    int *p7 = search_n(arr, arr + nSize, 3, 2);
    if (p7 != arr + nSize) {
        cout << "首次出现3个2的位置：" << p7 - arr << endl;
    }
    return 0;
}

