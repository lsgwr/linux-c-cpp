/***********************************************************
 * @Description : 获取全排列
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 17:07
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int a[] = {0, 0, 1, 1, 3, 2};
    sort(a, a+6);
    if (a[0] == 0) {
        int *it = upper_bound(a, a+6, 0);
        swap(a[0], *it);
    }
    do{
        copy(a, a+6, ostream_iterator<int>(cout, "\t"));
        cout << endl;
    }while (next_permutation(a, a+6));
    return 0;
}