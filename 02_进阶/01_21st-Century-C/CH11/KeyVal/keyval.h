//
// Created by Administrator on 2022/5/31.
//

#ifndef KEYVAL_KEYVAL_H
#define KEYVAL_KEYVAL_H

typedef struct keyval {
    char *key;
    void *val;
} keyval;

keyval *keyval_new(char *key, void *val);

keyval *keyval_copy(keyval const *in);

void keyval_free(keyval *in);

int keyval_matches(keyval const *in, char const *key);

#endif //KEYVAL_KEYVAL_H
