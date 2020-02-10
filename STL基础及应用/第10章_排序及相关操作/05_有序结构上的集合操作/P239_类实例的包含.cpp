/***********************************************************
 * @Description : P239_类实例的包含
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/10 11:09
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

class Student {
public:
    int no;
    string name;

    bool operator<(const Student &stu) const {
        return no < stu.no;
    }
};

int main() {
    bool bRet = true;
    Student s1[] = {{1001, "zhang"},
                    {1003, "li"},
                    {1004, "wang"},
                    {1002, "zhao"}};
    Student s2[] = {{1001, "zhang"},
                    {1004, "wang"},
                    {1002, "zhao"}};
    sort(s1, s1 + 4);
    sort(s2, s2 + 3);
    bRet = includes(s1, s1 + 4, s2, s2 + 3);
    cout << (bRet ? "s1包含s2" : "s1不包含s2") << endl;
    return 0;
}
/**
s1包含s2
*/