//
// Created by Administrator on 2022/5/31.
//

#include "keyval.h"

#include <stdlib.h> // malloc
#include <strings.h> // strcasecmp(from POSIX)

keyval *keyval_new(char *key, void *val) {
    keyval *out = malloc(sizeof(keyval));
    *out = (keyval) {.key = key, .val = val};
    return out;
}

/**
 * Copy a key/value pair, The new pair has pointers to
 * the values in the old pair, not copies of their data.
 */
keyval *keyval_copy(keyval const *in) {
    keyval *out = malloc(sizeof(keyval));
    *out = *in;
    return out;
}

void keyval_free(keyval *in) {
    free(in);
}

int keyval_matches(keyval const *in, char const *key) {
    return !strcasecmp(in->key, key);
}
