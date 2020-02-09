/***********************************************************
 * @Description : P199_remove简单示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 17:44
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    vector<int> v1(a, a + 9);

    cout << "删除前向量v1 = ";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    auto first = v1.begin();
    auto last = remove(v1.begin(), v1.end(), 2);

    cout << "删除后向量v1 = ";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "删除后有效  = ";
    copy(first, last, ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
删除前向量v1 = 1	2	3	4	5	4	3	2	1
删除后向量v1 = 1	3	4	5	4	3	1	2	1
删除后有效  = 1	3	4	5	4	3	1
*/