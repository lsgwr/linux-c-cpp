/***********************************************************
 * @Description : P194_生成随机数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 17:25
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <time.h>

using namespace std;

template<class T>
class MyRandom {

};

template<>
class MyRandom<int> {
public:
    MyRandom() {
        srand(time(nullptr));
    }

    int operator()() {
        int result = rand() % 100;
        return result;
    }
};

template<>
class MyRandom<float> {
public:
    MyRandom() {
        srand(time(nullptr));
    }

    float operator()() {
        float result = rand() % 100 * 0.01f;
        return result;
    }
};

int main() {
    cout << "产生[0, 100)间10个整型随机数：";
    vector<int> v1(10);
    generate_n(v1.begin(), 10, MyRandom<int>());
    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "产生[0, 1)间10个浮点随机数：";
    vector<float> v2(10);
    generate_n(v2.begin(), 10, MyRandom<float>());
    copy(v2.begin(), v2.end(), ostream_iterator<float>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
产生[0, 100)间10个整型随机数：44	4	17	72	38	84	87	80	34	1
产生[0, 1)间10个浮点随机数：0.44	0.04	0.17	0.72	0.38	0.84	0.87	0.8	0.34	0.01
*/