#include <stdio.h>
#include <math.h>

typedef struct point {
    double x, y;
} point;

typedef struct {
    struct point;
    double z;
} threepoint;

double threelength(threepoint p) {
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z); // 结果的开方25开方为5
}

int main() {
    threepoint p = {.x = 3, .y = 0, .z = 4};
    printf("p is %g units from the origin\n", threelength(p));
    return 0;
}
