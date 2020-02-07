/***********************************************************
 * @Description : P48_迭代器创建方式
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 23:29
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <string>

using namespace std;

int main() {
    string s1 = "How are you";
    string s2(s1.begin(), s1.end());
    string s3(s1.begin() + 4, s1.begin() + 7);
    return 0;
}