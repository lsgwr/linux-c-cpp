/***********************************************************
 * @Description : P226_list容器排序问题
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 22:33
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {10, 1, 3, 9, 7, 6, 2, 4, 5, 8};
    list<int> l(a, a+10);
    l.sort();
    copy(l.begin(), l.end(), ostream_iterator<int>(cout, "\t"));
    return 0;
}
/**
1	2	3	4	5	6	7	8	9	10
*/