/***********************************************************
 * @Description : P170_求数组中有多少个0
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 11:26
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int arr[] = {2, 0, 4, 6, 0, 0, -7};
    int N = sizeof(arr) / sizeof(arr[0]);
    cout << "数组arr中0的个数为："<< count(arr, arr+N, 0) << endl;
    return 0;
}
/**
数组arr中0的个数为：3
*/