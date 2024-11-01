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
        if (arr->data) free(arr->data);
        free(arr);
    }
}

void *array_at(array_t *arr, int element_number) {
    void *result = NULL;
    if (!arr) return result;
    if (element_number >= arr->length || element_number < 0) return result;
    return arr->data + (element_number * arr->element_size);
}

bool array_empty(array_t *arr) {
    if (!arr) return true;
    return arr->length == 0;
}

int array_size(array_t *arr) {
    if (!arr) return false;
    return arr->length;
}

bool array_copy(array_t **copy, array_t *original) {
    if (!original) return false;
    if ((*copy = malloc(sizeof(array_t))) == NULL) return false;
    (*copy)->length = original->length;
    (*copy)->element_size = original->element_size;
    if (original->data) {
        if (((*copy)->data = malloc((*copy)->length * (*copy)->element_size)) == NULL) {
            free(*copy);
            return false;
        }
        memcpy((*copy)->data, original->data, original->length * original->element_size);
    }
    return true;
}

bool array_push_back(array_t *arr, void *element) {
    bool result = true;
    if (arr) {
        if (arr->data) {
            uint8_t *tmp = realloc(arr->data, (arr->length + 1) * arr->element_size);
            if (tmp) {
                arr->data = tmp;
                memcpy(arr->data + (arr->length * arr->element_size), element, arr->element_size);
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
