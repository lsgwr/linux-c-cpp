#include <stdio.h>

#define Testclaim(assertion, returnval) if(!(assertion)) \
    {fprintf(stderr, #assertion " failed to be true.  \
    Returning " #returnval "\n"); return returnval;}

int do_things() {
    int x, y;
    Testclaim(x == y, -1);
    return 0;
}

void do_other_thing() {
    int x, y;
    Testclaim(x == y,); // 默认参数为空就是return;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
