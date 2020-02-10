/***********************************************************
 * @Description : STL实现trim功能
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 17:43
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <iostream>

using namespace std;

int main() {
    string s = " hello ";
    s.erase(s.find_last_not_of(" ") + 1); // 删除右空格
    cout << s << endl;
    s.erase(0, s.find_first_not_of(" ")); // 删除左空格
    cout << s << endl;
    return 0;
}
