/***********************************************************
 * @Description : P52_在字符串中删除字符
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 16:32
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s1 = "How are you?";
    s1.erase(s1.begin(), s1.begin() + 3);
    cout << "after erase s1 is:" << s1 << endl;

    string s2 = "Fine, thanks";
    s2.erase(s2.begin(), s2.end());
    cout << "after erase s2 is:" << s2 << endl;
    return 0;
}
/**
after erase s1 is: are you?
after erase s2 is:
*/