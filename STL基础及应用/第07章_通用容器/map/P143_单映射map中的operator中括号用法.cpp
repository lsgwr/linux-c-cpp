/***********************************************************
 * @Description : P143_单映射map中的operator中括号用法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 23:08
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <map>

using namespace std;

void display(map<string, string> &m) {
    auto it = m.begin();
    while (it != m.end()) {
        cout << (*it).first << "\t" << (*it).second << endl;
        it++;
    }
    cout << endl;
}

int main() {
    map<string, string> myMap;
    myMap["1-1"] = "元旦";
    myMap["5-1"] = "劳动节";
    myMap["7-1"] = "建党节";
    myMap["8-1"] = "建军节";
    myMap["10-1"] = "国庆节";
    string s = myMap["8-1"];
    cout << "打印出map:" << endl;
    display(myMap);
    cout << "查询10-1："<<s << endl;
    return 0;
}