#include "string.h"

String::String() {

}

String::String(const char* s) {
    copy(s);
}

String::~String() {
    delete[] data;
}

const char* String::remove() {
    const char* temp = data;
    data = nullptr;
    length = 0;
    return temp;
}

void String::copy(const char* s) {
    char* pos;
    while (*pos) {
        ++pos;
    }

    copy(s, pos - s);
}

void String::copy(const char* s, size_t len) {
    if (len > length) {
        delete[] data;
    }

    char* result = new char[len + 1];
    for (size_t i = 0; i < len; ++i) {
        result[i] = s[i];
    }
    result[len] = '\0';

    data = result;
    length = len;
}