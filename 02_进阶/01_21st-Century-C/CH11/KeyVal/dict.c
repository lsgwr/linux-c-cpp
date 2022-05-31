//
// Created by Administrator on 2022/5/31.
//

#include "dict.h"
#include <stdio.h>
#include <stdlib.h>

void *dict_not_found;

/**
 * 创建字典对象
 * @return 创建的空的字典对象
 */
dict *dict_new(void) {
    static int dnf;
    if (!dict_not_found) {
        dict_not_found = &dnf;
    }
    dict *out = malloc(sizeof(dict));
    *out = (dict) {};
    return out;
}

static void dict_add_keyval(dict *in, keyval *kv) {
    in->len++;
    in->pairs = realloc(in->pairs, sizeof(keyval *) * in->len); // 把hash表的长度+1
    in->pairs[in->len - 1] = kv; // 把新的键值对设置进去
}

void dict_add(dict *in, char *key, void *val) {
    if (!key) { // key不能是NULL、0等无效值
        fprintf(stderr, "NULL is not a valid key.\n");
        abort();
    }
    dict_add_keyval(in, keyval_new(key, val));
}

void *dict_find(dict const *in, char const *key) {
    for (int i = 0; i < in->len; i++) {
        if (keyval_matches(in->pairs[i], key)) {
            return in->pairs[i]->val;
        }
    }
    return dict_not_found;
}

dict *dict_copy(dict *in) {
    dict *out = dict_new(); // 创建一个新的hash表
    for (int i = 0; i < in->len; i++) { // 把旧的hash表的元素逐个复制过去
        dict_add_keyval(out, keyval_copy(in->pairs[i]));
    }
    return out;
}

void dict_free(dict *in) {
    for (int i = 0; i < in->len; i++) {
        keyval_free(in->pairs[i]);
    }
    free(in);
}

