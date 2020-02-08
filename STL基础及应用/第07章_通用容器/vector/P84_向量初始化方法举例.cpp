/***********************************************************
 * @Description : P84_向量初始化方法举例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 10:06
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <vector>
using namespace std;

// 无意义，仅是为了说明问题
class A{

};
int main(){
    vector<int> int_ect;
    vector<float> float_vect;
    vector<A> cA_vect;
    vector<A*> cpA_vect;

    cout << "init success" << endl;
    return 0;
}