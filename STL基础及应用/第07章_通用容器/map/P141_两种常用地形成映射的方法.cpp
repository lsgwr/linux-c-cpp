/***********************************************************
 * @Description : P141_两种常用地形成映射的方法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 23:00
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <map>

using namespace std;

void display(map<int, string> &m) {
    auto it = m.begin();
    while (it != m.end()) {
        cout << (*it).first << "\t" << (*it).second << endl;
        it++;
    }
    cout << endl;
}

int main() {
    map<int, string> myMap;
    pair<int, string> m1(1, "张三");
    pair<int, string> m2(2, "李四");
    pair<int, string> m3(3, "王五");
    pair<int, string> m4(4, "赵六");
    pair<int, string> m5(1, "张三");
    myMap.insert(m1);
    myMap.insert(m2);
    myMap.insert(m3);
    myMap.insert(m4);
    myMap.insert(m5);
    cout << "通过insert函数创建：" << endl;
    display(myMap);
    cout << "通过赋值构造函数创建：" << endl;
    map<int,string> myMap2(myMap);
    display(myMap2);
    return 0;
}
/**
通过insert函数创建：
1	张三
2	李四
3	王五
4	赵六

通过赋值构造函数创建：
1	张三
2	李四
3	王五
4	赵六
*/