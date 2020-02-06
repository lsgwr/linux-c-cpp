/***********************************************************
 * @Description : P33_get和getline函数示例
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 19:48
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

int main() {
    char szBuf[60];
    cout << "请输入一个字符串：";
    int n = cin.get(); // 先接收一个字符
    cin.getline(szBuf, 60); // 再接收一行字符串
    cout << n << endl;
    cout << "读入的字符串为：" << szBuf << endl;
    return 0;
}
/**
请输入一个字符串：How are you
72
读入的字符串为：ow are you
 */
