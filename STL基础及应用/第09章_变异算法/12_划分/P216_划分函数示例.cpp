/***********************************************************
 * @Description : P216_划分函数示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 20:59
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 7, 2, 5, 3, 4, 8, 2, 3, 6};
    vector<int> v(a, a+10);
    cout << "原始数据：";
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "按小于4条件划分(partition)， 小于4的放在前面：";
    partition(v.begin(), v.end(), bind2nd(less<int>(), 4));
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "按小于4条件划分(stable_partition)， 小于4的放在前面：";
    stable_partition(v.begin(), v.end(), bind2nd(less<int>(), 4));
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
原始数据：1	7	2	5	3	4	8	2	3	6
按小于4条件划分(partition)， 小于4的放在前面：1	3	2	2	3	4	8	5	7	6
按小于4条件划分(stable_partition)， 小于4的放在前面：1	3	2	2	3	4	8	5	7	6
*/