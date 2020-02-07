/***********************************************************
 * @Description : P47_字符串的基本创建方式
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 23:26
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <string>

using namespace std;

int main() {
    string s1;
    string s2("How are you?");
    string s3(s2);
    string s4(s2, 0, 3);
    string s5 = "Fine";
    string s6 = s2 + "Fine";
    return 0;
}