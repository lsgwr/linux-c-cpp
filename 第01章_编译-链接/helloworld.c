#include <stdio.h>

#define NUM 100
int main(void)
{
    int a = NUM;
    printf("your score is %d\n", NUM);
    #if 1
    printf("condition code");
    #endif // 0
    return 0;
}
