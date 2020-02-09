/***********************************************************
 * @Description : P155_求vector的最大最小以及和
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 23:28
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

class PrintInfo {
private:
    int nSum;
    int nMax;
    int nMin;
    int count;

public:
    PrintInfo() : nSum(0), count(0) {}

    int getNSum() const {
        return nSum;
    }

    int getNMax() const {
        return nMax;
    }

    int getNMin() const {
        return nMin;
    }

    int getCount() const {
        return count;
    }

    void operator()(int x) {
        if (count == 0) {
            // 第一个元素
            nMax = x;
            nMin = x;
        } else {
            if (nMax < x) {
                nMax = x;
            }
            if (nMin > x) {
                nMin = x;
            }
        }
        nSum += x;
        count++;
    }
};

int main() {
    int arr[] = {1, 4, 2, 8, 5, 7};
    int N = sizeof(arr) / sizeof(arr[0]);

    PrintInfo p = for_each(arr, arr + N, PrintInfo());
    cout << "总和是：" << p.getNSum() << endl;
    cout << "最大值是：" << p.getNMax() << endl;
    cout << "最小值是：" << p.getNMin() << endl;
    return 0;
}
/**
总和是：27
最大值是：8
最小值是：1
*/