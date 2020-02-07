/***********************************************************
 * @Description : P54_利用STL拆分字符串
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 16:59
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    // 源串
    string strText = "How are you?";
    // 拆分结果串
    string strResult;
    // 用字符串输入流封装字符串
    istringstream istr(strText);

    while (!istr.eof()) { // 当非字符串输入流结尾
        istr >> strResult; // 读输入流并给变量赋值
        cout << "string=" << strResult << endl;
    }
    return 0;
}