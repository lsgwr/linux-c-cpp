/***********************************************************
 * @Description : 模板与运算法重载
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 15:46
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

class Student {
    char name[20];
    int grade;

public:
    Student(char name[], int grade) {
        strcpy(this->name, name);
        this->grade = grade;
    }

    bool operator>(Student &student) const {
        return grade > student.grade;
    }
};

template<class U, class V>
bool MyGreater(U &u, V &v) {
    return u > v;
}

bool MyGreater(int u, int v) {
    return u > v;
}


int main() {

    bool flag1 = MyGreater(1, 2);
    cout << flag1 << endl;
    bool flag2 = MyGreater(2, 1);
    cout << flag2 << endl;

    Student liang("abc", 28);
    Student wang("ab", 27);
    bool flag3 = MyGreater(liang, wang);
    cout << flag3 << endl;
    return 0;
}