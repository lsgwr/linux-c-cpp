/***********************************************************
 * @Description : P208_reverse
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 19:34
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5};

    vector<int> v1(a, a + 5);
    cout << "原始向量v1 = ";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v2(a, a+5);
    reverse_copy(v2.begin(), v2.end(), v2.begin());
    cout << "反转向量v2 = ";
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v3(a, a+5);
    vector<int> v4;
    reverse_copy(v3.begin(), v3.end(), back_inserter(v4));
    cout << "反转向量v3并复制到v4 = ";
    copy(v4.begin(), v4.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
原始向量v1 = 1	2	3	4	5
反转向量v2 = 5	4	3	4	5
反转向量v3并复制到v4 = 5	4	3	2	1
*/