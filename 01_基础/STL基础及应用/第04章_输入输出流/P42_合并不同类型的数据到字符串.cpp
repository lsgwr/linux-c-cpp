/***********************************************************
 * @Description : P42_合并不同类型的数据到字符串
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 21:49
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    cout << "type an int, float and s string：" << endl;
    int i;
    float f;
    string stuff;
    getline(cin, stuff);
    ostringstream os;
    os << "integer=" << i << endl;
    os << "float=" << f << endl;
    os << "string=" << stuff << endl;

    string result = os.str();
    cout << result << endl;
    return 0;
}
/**
type an int, float and s string：
1 3.14 how are you
integer=0
float=0
string=1 3.14 how are you
*/