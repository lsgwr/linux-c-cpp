/***********************************************************
 * @Description : 优先队列
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/12/1 22:31
 * @email       : liangshanguang2@gmail.com
***********************************************************/

#include <iostream>
#include <queue>
#include <utility>

using namespace std;

class Stu {
public:
    int no;
    string name;

    Stu(int no, string name) : no(no), name(std::move(name)) {}

    bool operator<(const Stu &rhs) const {
        return no < rhs.no;
    }

    bool operator>(const Stu &rhs) const {
        return no > rhs.no;
    }

};

// 类函数
class StuCmp {
public:
    bool operator()(const Stu &s1, const Stu &s2) const {
        return s1.name > s2.name;
    }
};

int main() {
    Stu a[] = {Stu(1, "Mary"), Stu(3, "John"), Stu(2, "Smith")};
    int n = sizeof(a) / sizeof(a[0]);
    // 类里面有自定义的<关系函数定义pq1
    priority_queue<Stu> pq1(a, a + n);
    cout << "pq1: ";
    // 按no递减输出
    while (!pq1.empty()) {
        cout << "[" << pq1.top().no << ", " << pq1.top().name << "]\t";
        pq1.pop();
    }
    cout << endl;

    // 使用自定义的比较类函数
    priority_queue<Stu, vector<Stu>, greater<Stu>> pq2(a, a + n);
    cout << "pq2: ";
    // 按no递增输出
    while (!pq2.empty()) {
        cout << "[" << pq2.top().no << ", " << pq2.top().name << "]\t";
        pq2.pop();
    }
    cout << endl;

    // 使用自定义类函数实现自定义排序
    priority_queue<Stu, vector<Stu>, StuCmp> pq3(a, a + n);
    cout << "pq3: ";
    // 按name递增输出
    while (!pq3.empty()) {
        cout << "[" << pq3.top().no << ", " << pq3.top().name << "]\t";
        pq3.pop();
    }
    cout << endl;
}