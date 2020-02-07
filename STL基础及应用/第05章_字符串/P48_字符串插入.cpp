/***********************************************************
 * @Description : 字符串插入
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 23:42
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s = "do";
    cout << "initial size is " << s.size() << endl;
    s.insert(0, "How ");
    s.append(" you ");
    s += "do";

    cout << "final size is:" << s.size() << endl;
    cout << s << endl;
    return 0;
}