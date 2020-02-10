/***********************************************************
 * @Description : P185_字符串加密后输出
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 16:12
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

/**
 * 加密类模板
 * @tparam T 数据类型
 */
template<class T>
class Encrypt {

};

/**
 * 模板特化
 */
template<>
class Encrypt<string> {
public:
    /**
     * 对字符串加密
     * @param src 原始字符串
     * @return 加密后的字符串
     */
    string operator()(const string &src) {
        string s = src;
        int len = s.length();
        for (char &it : s) {
            it = it + 1;
        }
        return s;
    }
};

int main() {
    string strText;
    vector<string> v;
    vector<string> vResult;
    ifstream in("data.txt");
    while (!in.eof()) {
        getline(in, strText, '\n');
        v.push_back(strText);
    }
    in.close();
    // data.txt里面的是abcdef
    transform(v.begin(), v.end(), back_inserter(vResult), Encrypt<string>());
    copy(vResult.begin(), vResult.end(), ostream_iterator<string>(cout, "\n"));
    return 0;
}
/**
 * bcdefg
 */
