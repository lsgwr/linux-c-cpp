/***********************************************************
 * @Description : P212_随机函数示例
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/9 20:16
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5};
    float b[] = {1.1f, 2.1f, 3.1f, 4.1f, 5.1f};
    char c[] = {'a', 'b', 'c', 'd', 'e'};

    cout << "原始a[]=";
    copy(a, a + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;
    random_shuffle(a, a + 5);
    cout << "random_shuffle之后：";
    copy(a, a + 5, ostream_iterator<int>(cout, "\t"));
    cout << endl;

    cout << "原始b[]=";
    copy(b, b + 5, ostream_iterator<float>(cout, "\t"));
    cout << endl;
    random_shuffle(b, b + 5);
    cout << "random_shuffle之后：";
    copy(b, b + 5, ostream_iterator<float>(cout, "\t"));
    cout << endl;

    cout << "原始c[]=";
    copy(c, c + 5, ostream_iterator<char>(cout, "\t"));
    cout << endl;
    random_shuffle(c, c + 5);
    cout << "random_shuffle之后：";
    copy(c, c + 5, ostream_iterator<char>(cout, "\t"));
    cout << endl;
    return 0;
}
/**
原始a[]=1	2	3	4	5
random_shuffle之后：5	4	2	3	1
原始b[]=1.1	2.1	3.1	4.1	5.1
random_shuffle之后：1.1	3.1	5.1	2.1	4.1
原始c[]=a	b	c	d	e
random_shuffle之后：a	c	e	b	d
*/