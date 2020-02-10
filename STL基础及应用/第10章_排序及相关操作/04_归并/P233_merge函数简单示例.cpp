/***********************************************************
 * @Description : P233_merge函数简单示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 10:41
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8};
    int result[8];
    merge(a, a + 4, b, b + 4, result);
    cout << "result[]：";
    copy(result, result + 8, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    int c[8] = {1, 3, 4, 8, 2, 5, 6, 7};
    cout << "原始c[]：";
    copy(c, c + 8, ostream_iterator<int>(cout, "\t"));
    cout << endl;
    inplace_merge(c, c + 4, c + 8);
    cout << "选取中间点merge后的c[]";
    copy(c, c + 8, ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
result[]：1	2	3	4	5	6	7	8
原始c[]：1	3	4	8	2	5	6	7
选取中间点merge后的c[]1	2	3	4	5	6	7	8
*/