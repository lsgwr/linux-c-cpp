#include <stdio.h>
#include "print_typedef.h"

int main() {
    save.print(&save);
    spend.print(&spend);
    textlist_print(&save);  // 指定了print
    textlist_print(&recipe); // 没指定print，使用默认函数
    return 0;
}
