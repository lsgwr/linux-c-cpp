/***********************************************************
 * @Description : P53_整型数据和字符串相互转化
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 16:48
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    // 将整型10转换成字符串"10"
    int n1 = 10;
    string s1;
    stringstream os1;
    os1 << n1;
    os1 >> s1;
    cout << "整型10转化成字符串10：" << s1 << endl;

    // 将字符串"123"转化成整型123
    int n2 = 0;
    string s2 = "123";
    stringstream os2;
    os2 << s2;
    os2 >> n2;
    cout << "字符串123转化成整型123：" << n2 << endl;
    return 0;
}

