//
// Created by Administrator on 2022/5/31.
//

#ifndef PRINT_TYPEDEF_PRINT_TYPEDEF_H
#define PRINT_TYPEDEF_PRINT_TYPEDEF_H

typedef struct textlist_s {
    char *title;
    char **items;
    int len;

    void (*print)(struct textlist_s *); // 打印当前结构体的函数
} textlist_s;

extern textlist_s save;
extern textlist_s spend;
extern textlist_s recipe;

void textlist_print(textlist_s *in);

#endif //PRINT_TYPEDEF_PRINT_TYPEDEF_H
