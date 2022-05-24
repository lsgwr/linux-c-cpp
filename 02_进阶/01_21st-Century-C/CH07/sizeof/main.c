#include <stdio.h>

#define Peval(cmd) printf(#cmd ": %g\n", cmd) // 字符串拼接到一起用#
#define RESULT(X, Y) X##Y


int main() {
    double *plist = (double[]) {1, 2, 3};
    double list[] = {1, 2, 3};
    Peval(sizeof(plist) / sizeof(double) + 0.0);
    Peval(sizeof(list) / sizeof(double) + 0.0);
    printf("You can use the preprocessor's string "
           "concatenation to break long strings of text "
           "in your program. I think this is easier than "
           "using backslashes, but be careful with spacing.\n");


    int userinfo = 40;
    printf("the result is %d\n", RESULT(user, info)); // the result is 40
    return 0;
}
