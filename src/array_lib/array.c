#include "array.h"

#include <stdlib.h>
#include <string.h>

array_t *array_new(int element_size) {
    array_t *result = malloc(sizeof(array_t));
    if (result && element_size > 0) {
        result->length = 0;
        result->element_size = element_size;
        result->data = NULL;
    }
    return result;
}

void array_destroy(array_t *arr) {
    if (arr) {
        if (arr->data)
            free(arr->data);
        free(arr);
    }
}

bool array_push_back(array_t *arr, void *element) {
    bool result = true;
    if (arr) {
        if (arr->data) {
            uint8_t *tmp = realloc(arr->data, (arr->length + 1) * arr->element_size);
            if (tmp) {
                arr->data = tmp;
                memcpy(arr->data + (arr->length * arr->element_size),
                       element,
                       arr->element_size);
                arr->length++;
            } else
                result = false;
        } else {
            if ((arr->data = malloc(arr->element_size)) != NULL) {
                memcpy(arr->data, element, arr->element_size);
                arr->length++;
            } else
                result = false;
        }
    } else
        result = false;
    return result;
}
