/* upper.c */
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    int ch;

    while((ch = getchar()) != EOF) {
        putchar(toupper(ch));
    }

    return 0;
}
