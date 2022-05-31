//
// Created by Administrator on 2022/5/31.
//

#include <stdio.h>
#include "print_typedef.h"

static void print_ad(textlist_s *in) {
    printf("BUY THIS%s!!!! Features:\n", in->title);
    for (int i = 0; i < in->len; i++) {
        printf(". %s\n", in->items[i]);
    }
}

static void print_song(textlist_s *in) {
    printf("♫ %s ♫\nLyrics:\n\n", in->title);
    for (int i = 0; i < in->len; i++) {
        printf("\t%s\n", in->items[i]);
    }
}

void textlist_print(textlist_s *in) {
    if (in->print) { // 指定了print函数才去调用
        in->print(in);
        return;
    }
    printf("Title: %s\n\nItems:\n", in->title); // 不提供打印函数页给一个默认的
    for (int i = 0; i < in->len; i++) {
        printf("\t%s\n", in->items[i]);
    }
}

textlist_s save = {
        .title = "God Save the Queen",
        .len = 3,
        .items = (char *[]) { // 双层指针指向字符串数组
                "There's no future", "No future", "No future for me."
        },
        .print = print_song
};

textlist_s spend = {
        .title = "Never mind the Bollocks LP",
        .items = (char *[]) {
                "By the Sex Pistols", "Anti-consumption themes"
        },
        .len = 2,
        .print = print_ad
};

textlist_s recipe = {
        .title = "1 egge for baking",
        .len = 2,
        .items = (char *[]) {
                "1 Tbsp ground flax seeds", "3 Tbsp water"
        }
};


