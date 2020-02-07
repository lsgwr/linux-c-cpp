/***********************************************************
 * @Description : P54_利用STL拆分字符串
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 16:59
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <string>

using namespace std;

int main() {
    // 源串
    string strText = "How are you?";
    // 按空格拆分
    string strSeparator = " ";
    // 拆分结果串
    string strResult;
    // 拆分子串结束位置
    int size_pos = 0;
    // 拆分子串开始位置
    int size_prev_pos = 0;
    while ((size_pos = strText.find_first_of(strSeparator, size_pos)) != string::npos) {// 找到子串
        strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos); // 取子串
        cout << "string=" << strResult << endl;
        // 下一子串起始位置、结束位置 = 当前子串结束位置 + 1
        size_prev_pos = size_pos++;
    }
    if (size_prev_pos != strText.size()) { // 判断有无最后一个子串
        strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
        cout << "string=" << strResult << endl;
    }
    return 0;
}