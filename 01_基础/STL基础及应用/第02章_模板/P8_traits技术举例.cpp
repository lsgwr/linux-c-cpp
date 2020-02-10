/***********************************************************
 * @Description : traits技术举例
 * traits的思想：依靠显示模板特殊化来把代码中因类型不同而发生变化的片段拖出来，用统一的接口来封装
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 10:37
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class CIntArray {
    int a[10];

public:
    CIntArray() {
        for (int i = 0; i < 10; ++i) {
            a[i] = i;
        }
    }

    /**
     * 获取数组a元素之和的times倍
     * @param times 数组和的倍数
     * @return 数组和的times倍
     */
    int getSum(int times) {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += a[i];
        }
        return sum * times;
    }
};

class CFloatArray {
    float f[10];

public:
    CFloatArray() {
        for (int i = 0; i < 10; ++i) {
            f[i] = i;
        }
    }

    /**
     * 获取数组a元素之和的times倍
     * @param times 数组和的倍数
     * @return 数组和的times倍
     */
    float getSum(float times) {
        float sum = 0.0f;
        for (int i = 0; i < 10; ++i) {
            sum += f[i];
        }
        return sum * times;
    }
};

// traits
template<class T>
float getSum(T &t, float times) {
    return t.getSum(times);
}

int main() {
    CIntArray intArray;
    CFloatArray floatArray;
    cout << "整形数组和的3倍是：" << intArray.getSum(3) << endl;
    cout << "浮点数组的3.33倍是：" << floatArray.getSum(3.33f) << endl;
    // traits
    cout << "整形数组和的3倍是：" << getSum<CIntArray>(intArray, 3) << endl;
    cout << "浮点数组的3.33倍是：" << getSum<CFloatArray>(floatArray, 3.33) << endl;
    return 0;
}