/***********************************************************
 * @Description : P181_swap举例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 15:47
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    int a = 10, b = 20;

    cout << "原始的数据 a = " << a << "\tb=" << b << endl;
    swap(a, b);
    cout << "交换后数据 a = " << a << "\tb=" << b << endl;

    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {6, 7, 8, 9, 10};

    cout << "原始arr1：";
    copy(arr1, arr1 + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原始arr2：";
    copy(arr2, arr2 + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    swap_ranges(arr1, arr1 + 5, arr2);
    cout << "交换后的arr1：";
    copy(arr1, arr1 + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "交换后的arr2：";
    copy(arr2, arr2 + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    int arr3[5] = {10, 20, 30, 40, 50};
    int arr4[5] = {15, 25, 35, 45, 55};
    vector<int> v1(arr3, arr3 + 5);
    vector<int> v2(arr4, arr4 + 5);

    cout << "原始v1：";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原始v2：";
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    swap(v1,v2);

    cout << "交换后的v1：";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "交换后的v2：";
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}