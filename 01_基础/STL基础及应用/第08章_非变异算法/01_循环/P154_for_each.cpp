/***********************************************************
 * @Description : for_each
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 23:20
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 打印n的立方
 */
void printCube(int n) {
    cout << n * n * n << "\t";
}

int main() {
    const int VECTOR_SIZE = 8;
    vector<int> numberVec(VECTOR_SIZE); // 初始化容量为8的一个vector

    for (int i = 0; i < VECTOR_SIZE; ++i) {
        numberVec[i] = i + 1;
    }

    cout << "打印向量中的各个元素：";
    for (int num:numberVec) {
        cout << num << "\t";
    }
    cout << endl;

    cout << "打印vector中每个元素的立方：";
    for_each(numberVec.begin(), numberVec.end(), printCube);
    return 0;
}
/**
打印向量中的各个元素：1	2	3	4	5	6	7	8
打印vector中每个元素的立方：1	8	27	64	125	216	343	512
*/