/***********************************************************
 * @Description : P51_字符串查询函数基本用法
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 23:50
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <string>
#include <iostream>

using namespace std;

int main() {
    string s = "what's your name?my name is TOM. How do you do?Fine, thanks";
    int n = s.find("your");
    cout << "the first your pos:" << n << endl;
    n = s.find("you", 15);
    cout << "the first your pos begin from 15:" << n << endl;
    n = s.find_first_of("abcde");
    cout << "find pos when char within abcde:" << n << endl;
    n = s.find_first_of("abcde", 3);
    cout << "find pos begin from 2 when char within abcde:" << n << endl;
    return 0;
}
/**
the first your pos:7
the first your pos begin from 15:40
find pos when char within abcde:2
find pos begin from 2 when char within abcde:13
 */
