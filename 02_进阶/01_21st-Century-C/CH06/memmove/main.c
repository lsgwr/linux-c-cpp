#include <stdio.h>
#include <assert.h>
#include <string.h> // memmove函数所在文件

int main() {
    int abc[] = {0, 1, 2};
    int *copy1, copy2[3];
    copy1 = abc;
    memmove(copy2, abc, sizeof(int) * 3);
    return 0;
}
