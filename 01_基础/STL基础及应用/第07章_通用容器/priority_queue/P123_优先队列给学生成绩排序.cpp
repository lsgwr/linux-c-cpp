/***********************************************************
 * @Description : P123_优先队列给学生成绩排序
 * 排序原则：总成绩由高到低，如果分数相同，语文高者优先
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 20:59
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

class Student {
    int no; // 学号
    string name; // 姓名
    int chinese; //语文
    int math; // 数学

public:
    Student(int no, string name, int chinese, int math) : no(no), name(std::move(name)), chinese(chinese), math(math) {}

    int getNo() const {
        return no;
    }

    const string &getName() const {
        return name;
    }

    int getChinese() const {
        return chinese;
    }

    int getMath() const {
        return math;
    }

    bool operator<(const Student &stu) const {
        int sum1 = chinese + math;
        int chinese2 = stu.getChinese();
        int math2 = stu.getMath();
        int sum2 = chinese2 + math2;

        if (sum1 < sum2) {
            return true;
        }
        if ((sum1 == sum2) && (chinese < chinese2)) {
            return true;
        }
        return false;
    }
};

int main() {
    Student stus[] = {
            Student(1001, "张三", 70, 80),
            Student(1002, "李四", 80, 70),
            Student(1003, "王五", 90, 85),
            Student(1004, "赵六", 75, 75),
    };
    priority_queue<Student> pq(stus, stus + 4);
    while (!pq.empty()) {
        const Student &t = pq.top(); // 当前成绩最高的同学
        cout << t.getNo() << "\t" << t.getName() << "\t" << t.getChinese() << "\t" << t.getMath() << endl;
        pq.pop();
    }
    return 0;
}
/**
1003	王五	90	85
1002	李四	80	70
1004	赵六	75	75
1001	张三	70	80
*/