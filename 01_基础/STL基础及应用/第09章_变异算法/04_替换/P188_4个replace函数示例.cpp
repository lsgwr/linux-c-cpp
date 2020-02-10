/***********************************************************
 * @Description : P188_4个replace函数示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 16:40
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    int a[9] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    cout << "原始数据：";
    copy(a, a + 9, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原数据2用10代替(replace)：";
    vector<int> v1(a, a + 9);
    replace(v1.begin(), v1.end(), 2, 10);
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原数据小于4的用20代替(replace_if)：";
    vector<int> v2(a, a + 9);
    replace_if(v2.begin(), v2.end(), bind2nd(less<int>(), 4), 20);
    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原数据4的用30代替并复制到新vector(replace_copy)：";
    vector<int> v3(a, a + 9);
    vector<int> v4;
    replace_copy(v3.begin(), v3.end(), back_inserter(v4), 4, 30);
    copy(v4.begin(), v4.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原数据小于4的用40代替并复制到新vector(replace_copy)：";
    vector<int> v5(a, a + 9);
    vector<int> v6;
    replace_copy_if(v5.begin(), v5.end(), back_inserter(v6), bind2nd(less<int>(),4), 40);
    copy(v6.begin(), v6.end(), ostream_iterator<int>(cout, "\t"));
    return 0;
}
/**
原始数据：1	2	3	4	5	4	3	2	1
原数据2用10代替(replace)：1	10	3	4	5	4	3	10	1
原数据小于4的用20代替(replace_if)：20	20	20	4	5	4	20	20	20
原数据4的用30代替并复制到新vector(replace_copy)：1	2	3	30	5	30	3	2	1
原数据小于4的用40代替并复制到新vector(replace_copy)：40	40	40	4	5	4	40	40	40
*/