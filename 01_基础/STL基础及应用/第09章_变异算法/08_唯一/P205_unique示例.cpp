/***********************************************************
 * @Description : P205_unique示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 19:17
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 2, 2, 3, 4, 2, 2, 5};
    vector<int> v1(a, a + 8);
    cout << "原始向量：";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    auto last = unique(v1.begin(), v1.end());

    cout << "unique后向量v1：";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "unique后向量v1有效元素：";
    copy(v1.begin(), last, ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
原始向量：1	2	2	3	4	2	2	5
unique后向量v1：1	2	3	4	2	5	2	5
unique后向量v1有效元素：1	2	3	4	2	5
*/