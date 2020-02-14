/***********************************************************
 * @Description : P247 输入输出控制
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/13 22:54
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int a;
    cin >> a;
    // 以十进制形式输出整数
    cout << "dec:" << dec << a << endl;
    // 以十六进制形式输出整数
    cout << "hex:" << hex << a << endl;
    // 以8进制形式输出整数
    cout << "oct:" << setbase(8) << a << endl;

    // pt指向字符串
    char *pt = "HelloWorld";
    // 设定域宽为20，输出字符串
    cout << setw(20) << pt << endl;
    // 设定域宽为20，输出字符串，空白处以*填充
    cout << setfill('*') << setw(20) << pt << endl;

    double pi = 22.0 / 7.0;
    // 按指数形式输出，8位小数
    cout << setiosflags(ios::scientific) << setprecision(8) << endl;
    // 输出pi值
    cout << "pi = " << pi << endl;
    // 改为4位小数
    cout << "pi = " << setprecision(4) << pi << endl;
    // 改为小数形式输出
    cout << "pi = " << setiosflags(ios::fixed) << pi << endl;
    return 0;
}
/**
123
123
dec:123
hex:7b
oct:173
          HelloWorld
**********HelloWorld

pi = 3.14285714e+00
pi = 3.1429e+00
pi = 0x1.9249249249249p+1
*/