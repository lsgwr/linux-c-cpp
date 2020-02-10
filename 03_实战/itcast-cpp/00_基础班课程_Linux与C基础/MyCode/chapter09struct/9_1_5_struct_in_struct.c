/***********************************************************
 * @Description : 结构体嵌套结构体
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 7:57
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

struct person {
    char name[20];
    char sex;
};

struct stu {
    int id;
    struct person info;
};

int main() {
    struct stu s[3] = {
            {1, "张三", 'F'},
            {2, "李四", 'M'},
            {3, "王五", 'M'}
    };
    for (int i = 0; i < 3; ++i) {
        printf("id = %d\t name = %s\t sex = %c\n", s[i].id, s[i].info.name, s[i].info.sex);
    }
    return 0;
}
/**
id = 1	 name = 张三	 sex = F
id = 2	 name = 李四	 sex = M
id = 3	 name = 王五	 sex = M
 */
