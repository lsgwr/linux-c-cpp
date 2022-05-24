#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void wail() {
    fprintf(stderr, "0000ooooooo.\n");
}

void on_death() {
    for (int i = 0; i < 4; i++) {
        fprintf(stderr, "I'm dead.\n");
    }
}

_Noreturn void the_count() {
    for (int i = 5; i-- > 0;) {
        printf("%i\n", i);
        sleep(1);
    }
    // quick_exit(1);
    // _Exit(1);
    exit(1);
}

int main() {
    at_quick_exit(wail);
    atexit(wail);

    atexit(on_death);
    the_count();
    return 0;
}
/**
quick_exit(1):
4
3
2
1
0
0000ooooooo.

_Exit(1):
4
3
2
1
0

exit(1):
4
3
2
1
0
I'm dead.
I'm dead.
I'm dead.
I'm dead.
0000ooooooo.
 */
