/***********************************************************
 * @Description : P189_replace的易错案例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 16:51
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {2, 1, 3, 2, 2, 5};
// 注释的写法是不对的！！
//    replace(a, a + 6, a[0], 10);
//    copy(a, a + 6, ostream_iterator<int>(cout, "\t")); // 10	1	3	2	2	5
    int vold = a[0];
    replace(a, a + 6, vold, 10);
    copy(a, a + 6, ostream_iterator<int>(cout, "\t")); // 10	1	3	2	2	5
    return 0;
}