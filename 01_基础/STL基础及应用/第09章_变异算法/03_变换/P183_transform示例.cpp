/***********************************************************
 * @Description : P183_transform示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 16:00
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int func1(int val) {
    return val * 2;
}

int func2(int val1, int val2) {
    return val1 + val2;
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    vector<int> v1(arr, arr + 5);
    vector<int> v2(5);

    cout << "原始v1：";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "v1*2 --> v1 = ";
    transform(v1.begin(), v1.end(), v1.begin(), func1);
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "v1*2 --> v2 = ";
    transform(v1.begin(), v1.end(), v2.begin(), func1);
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    int arr2[5] = {1, 2, 3, 4, 5};
    int arr3[5] = {6, 7, 8, 9, 10};
    int arr4[5];

    cout << "原始arr2：";
    copy(arr2, arr2 + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原始arr3：";
    copy(arr3, arr3 + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "arr2+arr3-->arr4=";
    transform(arr2, arr2+5, arr3, arr4, func2);
    copy(arr4, arr4+5, ostream_iterator<int>(cout, "\t"));
    return 0;
}
/**
原始v1：1	2	3	4	5
v1*2 --> v1 = 2	4	6	8	10
v1*2 --> v2 = 4	8	12	16	20
原始arr2：1	2	3	4	5
原始arr3：6	7	8	9	10
arr2+arr3-->arr4=7	9	11	13	15
*/