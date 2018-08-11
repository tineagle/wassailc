#pragma once

#define DEFINE_ARRAY(name, dataType) \
typedef struct name##Array {         \
    uint32_t count;                  \
    dataType* data;                  \
} name##Array;