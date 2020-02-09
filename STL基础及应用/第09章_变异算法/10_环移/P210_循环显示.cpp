/***********************************************************
 * @Description : P210_循环显示
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 19:43
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iterator>

using namespace std;

// 1s延时程序
void delay() {
    int start = time(nullptr);
    auto end = start;
    do {
        if (start != end) {
            break;
        }
    } while (end = time(nullptr));
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> v(a, a + 8);
    cout << endl;
    while (true) {
        copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
        rotate(v.begin(), v.begin() + 1, v.end());
        delay();
        cout << endl;
    }
    return 0;
}
/**
1	2	3	4	5	6	7	8
2	3	4	5	6	7	8	1
3	4	5	6	7	8	1	2
4	5	6	7	8	1	2	3
5	6	7	8	1	2	3	4
6	7	8	1	2	3	4	5
......
*/