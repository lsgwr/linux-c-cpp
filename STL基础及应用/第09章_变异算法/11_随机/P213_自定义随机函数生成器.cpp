/***********************************************************
 * @Description : P213_自定义随机函数生成器
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 20:52
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

class MyRand {
public:
    int operator()(int n) {
        srand(time(nullptr));
        return rand() % n;
    }
};

int main() {
    int a[] = {10, 21, 32, 43, 54, 65, 76, 87, 98};
    vector<int> v(a, a+5);
    MyRand obj;
    random_shuffle(v.begin(), v.end(), obj);
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
43	54	32	21	10
*/