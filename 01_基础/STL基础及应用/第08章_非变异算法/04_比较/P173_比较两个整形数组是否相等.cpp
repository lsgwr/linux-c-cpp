/***********************************************************
 * @Description : P173_比较两个整形数组是否相等
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 11:49
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int arr1[] = {3, 1, 4, 1, 5, 9, 3};
    int arr2[] = {3, 1, 4, 2, 8, 5, 7};

    int N = sizeof(arr1) / sizeof(arr1[0]);
    cout << "比较结果：" << equal(arr1, arr1 + N, arr2) << endl;
    return 0;
}