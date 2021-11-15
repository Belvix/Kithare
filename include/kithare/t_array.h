/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#ifdef __cplusplus
extern "C" {
#endif
#ifdef khArray_TYPE

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <kithare/macros.h>


#ifndef khArray_NAME
#define khArray_NAME kh_CONCAT(khArray_, khArray_TYPE)
#endif
#define khArray_CONCAT(X) kh_CONCAT(khArray_NAME, _##X)


typedef struct {
    khArray_TYPE* array;
    size_t size;
    size_t reserved;
} khArray_NAME;


static inline khArray_NAME khArray_CONCAT(new)() {
    return (khArray_NAME){.array = NULL, .size = 0, .reserved = 0};
}

static inline khArray_NAME khArray_CONCAT(copy)(const khArray_NAME* array) {
    if (!array->array || !array->size) {
        return khArray_CONCAT(new)();
    }

    khArray_TYPE* ptr = (khArray_TYPE*)malloc(array->size * sizeof(khArray_TYPE));

#ifdef khArray_COPIER
    for (size_t i = 0; i < array->size; i++) {
        ptr[i] = khArray_COPIER(&array->array[i]);
    }
#else
    memcpy(ptr, array->array, array->size * sizeof(khArray_TYPE));
#endif

    return (khArray_NAME){.array = ptr, .size = array->size, .reserved = array->size};
}

static inline void khArray_CONCAT(delete)(khArray_NAME* array) {
    if (array->array) {
#ifdef khArray_DELETER
        for (size_t i = 0; i < array->size; i++) {
            khArray_DELETER(&array->array[i]);
        }
#endif

        free(array->array);
        array->array = NULL;
    }

    array->size = 0;
    array->reserved = 0;
}

static inline void khArray_CONCAT(reserve)(khArray_NAME* array, size_t size) {
    if (array->reserved >= size) {
        return;
    }

    if (array->array) {
        khArray_TYPE* ptr = (khArray_TYPE*)malloc(size * sizeof(khArray_TYPE));
        memcpy(ptr, array->array, array->size * sizeof(khArray_TYPE));
        free(array->array);
        array->array = ptr;
    }
    else {
        array->array = (khArray_TYPE*)malloc(size * sizeof(khArray_TYPE));
    }

    array->reserved = size;
}

static inline void khArray_CONCAT(fit)(khArray_NAME* array) {
    if (!array->array) {
        return;
    }

    if (array->size) {
        if (array->size == array->reserved) {
            return;
        }

        khArray_TYPE* ptr = (khArray_TYPE*)malloc(array->size * sizeof(khArray_TYPE));
        memcpy(ptr, array->array, array->size * sizeof(khArray_TYPE));
        free(array->array);
        array->array = ptr;
        array->reserved = array->size;
    }
    else {
        khArray_CONCAT(delete)(array);
    }
}

static inline void khArray_CONCAT(push)(khArray_NAME* array, khArray_TYPE item) {
    if (array->size == array->reserved) {
        khArray_CONCAT(reserve)(array, array->size ? array->size * 2 : 2);
    }

    array->array[array->size] = item;
    array->size++;
}

static inline void khArray_CONCAT(pushPtr)(khArray_NAME* array, const khArray_TYPE* item) {
    if (array->size == array->reserved) {
        khArray_CONCAT(reserve)(array, array->size ? array->size * 2 : 2);
    }

#ifdef khArray_COPIER
    array->array[array->size] = khArray_COPIER(item);
#else
    array->array[array->size] = *item;
#endif

    array->size++;
}

static inline void khArray_CONCAT(memory)(khArray_NAME* array, const khArray_TYPE* address,
                                          size_t size) {
    khArray_CONCAT(reserve)(array, array->size + size);

#ifdef khArray_COPIER
    for (size_t i = 0; i < size; i++) {
        array->array[array->size + i] = khArray_COPIER(&address[i]);
    }
#else
    memcpy(&array->array[array->size], address, size * sizeof(khArray_TYPE));
#endif

    array->size += size;
}

static inline khArray_NAME khArray_CONCAT(fromMemory)(const khArray_TYPE* address, size_t size) {
    khArray_NAME array = khArray_CONCAT(new)();
    khArray_CONCAT(memory)(&array, address, size);
    return array;
}

static inline void khArray_CONCAT(string)(khArray_NAME* array, const khArray_TYPE* string) {
    static char ZEROES[sizeof(khArray_TYPE)];
    static bool first = true; // TODO: handle the case of static variables in static functions
    if (first) {
        memset(ZEROES, 0, sizeof(khArray_TYPE));
        first = false;
    }

    size_t size = 0;
    for (;; size++) {
        if (!memcmp(&string[size], ZEROES, sizeof(khArray_TYPE))) {
            break;
        }
    }

    khArray_CONCAT(memory)(array, string, size);
}

static inline khArray_NAME khArray_CONCAT(fromString)(const khArray_TYPE* string) {
    khArray_NAME array = khArray_CONCAT(new)();
    khArray_CONCAT(string)(&array, string);
    return array;
}

static inline void khArray_CONCAT(concatenate)(khArray_NAME* array, const khArray_NAME* other) {
    if (!other->array) {
        return;
    }

    khArray_CONCAT(memory)(array, other->array, other->size);
}

static inline void khArray_CONCAT(pop)(khArray_NAME* array, size_t elements) {
    if (elements > array->size) {
        elements = array->size;
    }

#ifdef khArray_DELETER
    for (size_t i = elements; i > 0; i--) {
        khArray_DELETER(&array->array[array->size - i]);
    }
#endif

    array->size -= elements;
}


#ifdef khArray_COPIER
#undef khArray_COPIER
#endif

#ifdef khArray_DELETER
#undef khArray_DELETER
#endif

#undef khArray_NAME
#undef khArray_TYPE
#else
// Ignore this error from your IDE while editing this header
#error "`khArray_TYPE` hasn't been defined"
#endif
#ifdef __cplusplus
}
#endif
