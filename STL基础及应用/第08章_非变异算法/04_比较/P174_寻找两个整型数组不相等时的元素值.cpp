/***********************************************************
 * @Description : P174_寻找两个整型数组不相等时的元素值
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 11:52
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int arr1[] = {3, 1, 4, 1, 5, 9, 3};
    int arr2[] = {3, 1, 4, 2, 8, 5, 7};

    int N = sizeof(arr1) / sizeof(arr1[0]);
    // 返回不匹配位置的两个数组的对应元素的指针
    pair<int *, int *> result = mismatch(arr1, arr1 + N, arr2);
    cout << "不匹配位置的元素是：" << *(result.first) << ", " << *(result.second) << endl;
    return 0;
}
/**
不匹配位置的元素是：1, 2
*/