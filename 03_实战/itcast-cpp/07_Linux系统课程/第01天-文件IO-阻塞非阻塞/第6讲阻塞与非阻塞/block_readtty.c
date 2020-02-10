// 功能：从控制台输入啥就回显啥
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buf[10];
    int n;

    // #define STDIN_FILENO 0 // #define STDOUT_FILENO 1 // #define STDERR_FILENO 2
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0)
    {
        perror("read STDIN_FINENO");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);

    return 0;
}
