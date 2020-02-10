/***********************************************************
 * @Description : 命名空间
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 09:41
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <cstdio>

namespace my_company {
    void func() {
        printf("Hello, This is my company!\n");
    }
}

namespace your_company {
    void func() {
        printf("Hello, This is your company!\n");
    }
}

using namespace my_company;

int main(int argc, char *argv[]) {
    func();
    your_company::func();
    return 0;
}