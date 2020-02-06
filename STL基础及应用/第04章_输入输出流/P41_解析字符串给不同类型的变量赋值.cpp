/***********************************************************
 * @Description : P41_字符串输入输出流
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 21:42
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    int n;
    float f;
    string strHello;

    string strText = "1 3.14 hello";
    istringstream s(strText);
    s >> n;
    s >> f;
    s >> strHello;

    cout << "n=" << n << endl;
    cout << "f=" << f << endl;
    cout << "strHello=" << strHello << endl;
    return 0;
}
/**
n=1
f=3.14
strHello=hello
 */
