/***********************************************************
 * @Description : P211_list中环移函数用法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 19:58
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iterator>
#include <list>

using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    cout << "原始数据a[]=";
    copy(a, a + 8, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    list<int> v1(a, a + 8);
    auto middle = v1.begin();
    advance(middle, 3);
    rotate(v1.begin(), middle, v1.end());
    cout << "以4为中心环移(rotate)：";
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    list<int> v2(a, a + 8);
    list<int> v3;
     middle = v2.begin();
    advance(middle, 3);
    rotate_copy(v2.begin(), middle, v2.end(), back_inserter(v3));
    cout << "以4为中心环移(rotate)并把结果复制到v3：";
    copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
原始数据a[]=1	2	3	4	5	6	7	8
以4为中心环移(rotate)：4	5	6	7	8	1	2	3
以4为中心环移(rotate)并把结果复制到v3：4	5	6	7	8	1	2	3
*/