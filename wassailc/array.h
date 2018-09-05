#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define DEFINE_ARRAY(Name, Type)    \
typedef struct Name {               \
    uint32_t count;                 \
    Type* data;                      \
} Name;

#define FREE_ARRAY(arr) free((void*) arr.data)

#define VK_ENUMERATE(arr, fEnum) {                                      \
    fEnum(&arr.count, NULL);                                            \
    arr.data = malloc(sizeof(arr.data[0]) * arr.count);                 \
                                                                        \
    while (fEnum(&arr.count, arr.data) == VK_INCOMPLETE) {              \
        fEnum(&arr.count, NULL);                                        \
        arr.data = realloc(arr.data, sizeof(arr.data[0]) * arr.count);  \
    }                                                                   \
}

#define VK_ENUMERATE_ARGS(arr, fEnum, ...) {                            \
    fEnum(__VA_ARGS__, &arr.count, NULL);                               \
    arr.data = malloc(sizeof(arr.data[0]) * arr.count);                 \
                                                                        \
    while (fEnum(__VA_ARGS__, &arr.count, arr.data) == VK_INCOMPLETE) { \
        fEnum(__VA_ARGS__, &arr.count, NULL);                           \
        arr.data = realloc(arr.data, sizeof(arr.data[0]) * arr.count);  \
    }                                                                   \
}

#define CHECK_ARRAYS(found, xs, avails, prop) {                         \
    for(uint32_t i = 0; i < xs.count; ++i) {                            \
        if (found[i]) continue;                                         \
        for(uint32_t j = 0; j < avails.count; ++j) {                    \
            found[i] = strcmp(xs.data[i], avails.data[i].prop) == 0;    \
        }                                                               \
    }                                                                   \
}

#define VERIFY_ARRAYS(foundAll, found, arr) {                               \
    foundAll = true;                                                        \
    for(uint32_t i = 0; i < arr.count; ++i) {                               \
        printf("%s : %s\n", arr.data[i], (found[i] ? "FOUND" : "MISSING")); \
        foundAll &= found[i];                                               \
    }                                                                       \
}