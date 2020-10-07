#include "String.h"

int main() {
    String s1("Hello");        // 构造函数
    cout << s1 << endl;
    //String s2 = s1;          // 调用拷贝构造函数
    String s2(s1);             // 调用拷贝构造函数
    cout << s2 << endl;
    String s2A(std::move(s1));              // 移动构造函数
    cout << s2A << endl;
    String s3;                                        // 无参构造函数
    cout << s3 << endl;
    s3 = s2;                                           // 调用赋值函数
    cout << s3 << endl;
    String s3A;                                      // 无参构造函数
    s3A = std::move(s2A);                    // 移动赋值运算符
    cout << s3A << endl;

    return 0;
}
