#include <iostream> // std::cout
#include <vector> // std::vector
#include <algorithm> // std::sort
#include <functional> // std::binary_function
#include <iterator>

using namespace std;

bool MyCmp(int i, int j) {
    return i > j;
}

// 单独使用仿函数，通常将仿函数和算法单独分开使用
int main() {
    int myints[] = {32, 71, 12, 45, 26, 80, 53, 33};
    vector<int> myvec(myints, myints + 8); // 创建vector，32 71 12 45 26 80 53 33

    // 使用默认的比较器，默认升序排列
    sort(myvec.begin(), myvec.begin() + 4);  // (12 32 45 71)26 80 53 33
    copy(myvec.begin(), myvec.end(), ostream_iterator<int>(cout, "\t")); // 输出数组
    cout << endl;

    // 使用自定义的比较器,自定义降序排列最后四个元素
    sort(myvec.begin() + 4, myvec.end(), MyCmp); // 12	32	45	71	80	53	33	26
    copy(myvec.begin(), myvec.end(), ostream_iterator<int>(cout, "\t")); // 输出数组
    cout << endl;

    // 使用系统自带的比较器，降序排列
    sort(myvec.begin(), myvec.end(), std::greater<int>());
    copy(myvec.begin(), myvec.end(), ostream_iterator<int>(cout, "\t")); // 输出数组
    return 0;
}