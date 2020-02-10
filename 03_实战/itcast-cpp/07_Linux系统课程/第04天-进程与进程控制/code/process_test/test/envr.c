#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(void)
{
    int i;

    for (i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);

    printf("-----------------------\n");

    printf("PATH=%s\n", getenv("PATH"));
    setenv("DOG", "wangwangwang", 1);
    printf("dog=%s\n", getenv("DOG"));

    int ret = unsetenv("PIG=");
    if (ret == -1) {
        perror("unsetenv error");
        return 1;
    }
    printf("dog=%s\n", getenv("DOG"));

    return 0;
}
