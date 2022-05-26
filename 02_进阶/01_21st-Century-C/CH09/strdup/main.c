#include <stdio.h>
#include <string.h>

int main() {
    char *s1 = strdup("Thread"); // strdup可以让字符串是可变的
    s1[2] = 'M';
    printf("s1 = %s\n", s1);

    char *s2 = "Thread"; // strdup可以让字符串是可变的
    s2[2] = 'M'; // 字符串是不可变的，这个会报Segment Fault
    printf("s2 = %s\n", s2);
    return 0;
}
