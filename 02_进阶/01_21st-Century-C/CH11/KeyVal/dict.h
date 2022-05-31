//
// Created by Administrator on 2022/5/31.
//

#ifndef KEYVAL_DICT_H
#define KEYVAL_DICT_H

#include "keyval.h"

extern void *dict_not_found;

typedef struct dict {
    keyval **pairs;
    int len;
} dict;

dict *dict_new(void);

dict *dict_copy(dict *in);

void dict_free(dict *in);

void dict_add(dict *in, char *key, void *val);

void *dict_find(dict const *in, char const *key);

#endif //KEYVAL_DICT_H
