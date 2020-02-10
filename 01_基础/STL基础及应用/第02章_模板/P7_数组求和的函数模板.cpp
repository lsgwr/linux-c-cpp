/***********************************************************
 * @Description : 数组求和的函数模板
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 10:25
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

/**
 * 数组求和
 * @tparam T 数组类型
 * @param arr T类型的数组
 * @param nSize 数组的大小
 * @return
 */
template<class T>
T sum(T arr[], int nSize) {
    T sum = 0;
    for (int i = 0; i < nSize; ++i) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3};
    int result = sum<int>(arr, sizeof(arr) / sizeof(arr[0]));
    printf("数组之和为：%d\n", result);
    return 0;
}