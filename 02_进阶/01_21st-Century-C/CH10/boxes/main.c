#include <stdio.h>

typedef struct {
    char *name;
    int left, right, up, down;
} direction_s;

void this_row(direction_s d) {
    printf(d.left ? "*..\n" : d.right ? "..*\n" : ".*.\n");
}

void draw_box(direction_s d) {
    printf("%s:\n", (d.name ? d.name : "a box"));
    d.up ? this_row(d) : printf("...\n");
    (!d.up && !d.down) ? this_row(d) : printf("...\n");
    d.down ? this_row(d) : printf("...\n");
    printf("\n");
}

int main() {
    direction_s d = {.name = "left", .left = 1};
    draw_box(d);
    d = (direction_s) {"upper right", .up=1, .right=1};
    draw_box(d);
    draw_box((direction_s) {});
    return 0;
}
