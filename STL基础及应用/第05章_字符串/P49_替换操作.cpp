/***********************************************************
 * @Description : 替换操作
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 23:46
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <string>
#include <iostream>

using namespace std;

int main() {
    string s = "what's your name?";
    cout << "替换前：" << s << endl;
    s.replace(7, 4, "her");
    cout << "替换后：" << s << endl;
    return 0;
}
/**
替换前：what's your name?
替换后：what's her name?
 */
