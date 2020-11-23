/***********************************************************
 * @Description : 测试顺序表的功能
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/11/23 23:06
 * @email       : liangshanguang2@gmail.com
***********************************************************/

#include "SeqList.h"

int main() {
    SeqList<int> list(10);
    for (int i = 0; i < 10; i++) {
        list.insert(i * 10);
    }
    // 输出初始化后的顺序表
    for (int i = 0; i < list.getLen(); i++) {
        cout << list.get(i) << " ";
    }
    cout << endl;
    // 删除索引为3的元素
    list.del(3);
    // 输出删除元素后的顺序表
    for (int i = 0; i < list.getLen(); i++) {
        cout << list.get(i) << " ";
    }
    cout << endl;
    // 将顺序索引为5的元素值修改为44
    list.update(5, 44);
    // 输出修改后的顺序表
    for (int i = 0; i < list.getLen(); i++) {
        cout << list.get(i) << " ";
    }
    cout << endl;
    return 0;
}
/**输出如下
0 10 20 30 40 50 60 70 80 90
0 10 20 40 50 60 70 80 90
0 10 20 40 50 44 70 80 90
*/