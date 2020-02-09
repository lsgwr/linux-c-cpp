/***********************************************************
 * @Description : P201_remove_copy示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 18:47
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5};
    cout << "原始数据a[]=";
    copy(a, a + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v1(a, a + 5);
    auto last1 = remove_copy(v1.begin(), v1.end(), v1.begin(), 3); // 修改容器本身
    cout << "移去3后有效数据：";
    copy(v1.begin(), last1, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    vector<int> v2(a, a+5);
    vector<int> v3;
    cout << "移去3复制到另一容器数据：";
    remove_copy(v2.begin(), v2.end(), back_inserter(v3), 3); //  自身容器没修改
    copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, "\t"));
    return 0;
}
/**
原始数据a[]=1	2	3	4	5
移去3后有效数据：1	2	4	5
移去3复制到另一容器数据：1	2	4	5
*/