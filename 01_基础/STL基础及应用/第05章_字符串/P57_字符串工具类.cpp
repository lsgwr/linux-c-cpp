/***********************************************************
 * @Description : P57_字符串工具类
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/7 17:53
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class StringUtil : public string {
public:
    /**
     * 字符串转整型
     * @param str 字符串
     * @return 字符串对应的整型
     */
    int str2int(string str) {
        int n = 0;
        stringstream os;
        os << str;
        os >> n;
        return n;
    }

    /**
     * 整型转字符串
     * @param n 整型数
     * @return 整型转化后的字符串
     */
    string int2str(int n) {
        string str;
        stringstream os;
        os << n;
        os >> str;
        return str;
    }

    /**
     * 去掉字符串两边的空格
     * @param str 原始字符串
     * @return 去除空格后的字符串
     */
    string trim(string str) {
        str.erase(str.find_last_not_of(" ") + 1); // 删除右空格
        cout << str << endl;
        str.erase(0, str.find_first_not_of(" ")); // 删除左空格
    }
};

int main() {
    StringUtil stringUtil;
    // 1.字符串转整型
    int n = stringUtil.str2int("123");
    cout << n << endl;
    // 2.整型转字符串
    string s1 = stringUtil.int2str(456);
    cout << s1 << endl;
    // 3.去除两侧空格
    string s2 = stringUtil.trim("   hello ");
    cout << s2 << endl;
    return 0;
}

