#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stopif.h"

int main() {
    char *end;
    char *str = "12XX";
    double in = strtod(str, &end); // end指向第1个不能解析成数字的字母
    Stopif(*end, return 2, "I couldn't parse '%s' to a number. i had trouble with '%s'.", str, end);
    printf("The square of %s is %g\n", str, pow(in, 2));
    return 0;
}
/**
 * I couldn't parse '12XX' to a number. i had trouble with 'XX'.
 */
